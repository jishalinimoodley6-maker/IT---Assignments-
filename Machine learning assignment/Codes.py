
# Part A: : Data Acquisition and Understanding

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier

from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    confusion_matrix,
    classification_report
)

from sklearn.model_selection import GridSearchCV

df = pd.read_csv("german_credit_data.csv")

print(f"Shape : {df.shape}")
print(f"Columns : {df.columns}")
print(f"Information of the dataset : {df.info()}")
print(f"Description of the dataset  : {df.describe()}")
print(f"Missing values : {df.isnull().sum()}")

# Part B :  Exploratory Data Analysis (EDA)
# Dropping the index column only if it is present
if 'Unnamed: 0' in df.columns:
    df = df.drop(columns=['Unnamed: 0'])

# We assign the Target Variable 'Risk' using np.where()
df['Risk'] = np.where((df['Duration'] > 24) | (df['Credit amount'] > 4000), 'bad', 'good')

# Target Visualization:
fig, axes = plt.subplots(2, 2, figsize=(10, 5))

# Target Variable Distribution
sns.countplot(x='Risk', data=df, hue='Risk',ax=axes[0, 0], palette='Set3')
axes[0, 0].set_title(' Target Variable Distribution (Risk)', fontsize=12, fontweight='bold')
axes[0, 0].set_xlabel('Credit Risk')
axes[0, 0].set_ylabel('Count')

# Interpretation:
# The target variable distribution shows the number of customers that have been either a good or bad credit risk.
# The German Credit dataset has more customers  as good credit risks than bad credit risks, which shows
# that the target variable is slightly imbalanced. Although the imbalance is not extreme,
# it should be considered when evaluating the classification models because accuracy alone may not provide a complete picture of model performance.
# Therefore, additional evaluation metrics like precision, recall, F1-score and the confusion matrix should also be considered.

# Correlation HeatMap:
column_num = df.select_dtypes(include=[np.number]).columns
sns.heatmap(df[column_num].corr(), annot=True, cmap='Blues', fmt='.2f', ax=axes[0, 1])
axes[0, 1].set_title('Correlation Heatmap (Numerical Features)', fontsize=10, fontweight='bold')

# Interpretation :
# The correlation heatmap represents the direction of linear relationships between numerical variables.
# The variables do not all have strong correlations with one another,
# which shows that the dataset contains  different types of information about the credit candidates.
# Some variables show weak-to-moderate positive or negative relationships, while others have very little linear relationship.
# This is useful for identifying potential redundancy between variables.
# The correlation analysis also provides an initial understanding of the relationships between the predictors before applying PCA
# and developing the classification models.

#Box plots:

sns.boxplot(data=df[['Age', 'Duration', 'Credit amount']], ax=axes[1, 0], palette='Set3')
axes[1, 0].set_title(' Box plots for Numerical Features ', fontsize=12, fontweight='bold')

# Interpretation:
# The box plots are used to identify the spread of the numerical
# features and possible extreme values. The values appearing beyond the whiskers
# maybe potential outliers. However, an extreme value is not instantly
# an error because it may represent a valid characteristic of a website.

# Histograms :

sns.histplot(df['Credit amount'], kde=True, color='blue', ax=axes[1, 1], bins=30)
axes[1, 1].set_title('Distribution of Credit Amount', fontsize=12, fontweight='bold')

plt.tight_layout()
plt.show()

# Interpretation:

# The histograms show you the spread, median and outliers within the numerical variables.
# Age has a smaller range compared to the variation observed in the Credit amount.
# The Credit amount variable contains many observations that are considered higher than the majority of the dataset,
# showing the presence of the outliers.
# Duration indicates variation between customers and may contain some observations at the higher end of its range.
# These potential outliers should be investigated rather than automatically removed, as they may represent genuine credit applications.
# The box plots help to identify rare observations that could influence  machine learning algorithms.

# Part C
# Handle missing values :

if 'Unnamed: 0' in df.columns:
    df = df.drop(columns=['Unnamed: 0'])

category = df.select_dtypes(include=['object']).columns

for column in category:
    df[column] = df[column].fillna(df[column].mode()[0])

print(f"Missing values after treatment: {df.isnull().sum()}")

# Remove the duplicates

print(f"Duplicate rows before removal: {df.duplicated().sum()}")

df = df.drop_duplicates()

print(f"After removing the duplicates : {df.shape}")

# Justification:
# Duplicate records are removed because duplicate observations can cause
# some records to over-shape the machine learning results.
# X contains the independent variables/features

X = df.drop(columns=['Risk'])

# y contains the target variable
y = df['Risk']

print(f"Features: {X.columns}")

print(f"The target variable: {y.value_counts()}")


# Convert target variable into numbers
y = y.map({'good': 0, 'bad': 1})

# Treating outliers

column_num = X.select_dtypes(include=[np.number]).columns

Q1 = X[column_num].quantile(0.25)

Q3 = X[column_num].quantile(0.75)

IQR = Q3 - Q1

outliers = (
    (X[column_num] < (Q1 - 1.5 * IQR)) |
    (X[column_num] > (Q3 + 1.5 * IQR))
)

print("The outliers are:")
print(outliers.sum())

# Encode categorical variables

X = pd.get_dummies(
    X,
    drop_first=True
)

print(f"The dataset after categorical encoding: {X.head()}")

print(f"Shape after encoding: {X.shape}")


# Feature scaling

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.20,
    random_state=42,
    stratify=y
)


scaler = StandardScaler()

X_train_scaled = scaler.fit_transform(X_train)

X_test_scaled = scaler.transform(X_test)


print(f"Scaled training data shape: {X_train_scaled.shape}")

print(f"Scaled testing data shape: {X_test_scaled.shape}")


# Splitting and training sets

print(f"Training data shape: {X_train.shape}")

print(f"Testing data shape: {X_test.shape}")

print(f"Training target shape: {y_train.shape}")

print(f"Testing target shape: {y_test.shape}")

# Feature scaling is necessary as it features with larger ranges which may dominate
# others in distance-based algorithms like:
# K-Nearest Neighbors (KNN)
# K-Means Clustering
# Support Vector Machines (SVM)
# Feature scaling is a preprocessing step that adjusts input variables to a common range so no single feature overpowers the model.


# Part D
pca = PCA()

X_train_pca_full = pca.fit_transform(X_train_scaled)

# Display explained variance ratio
print(f"Explained Variance Ratio: {pca.explained_variance_ratio_}")

# Calculate cumulative explained variance
cumulative_variance = np.cumsum(pca.explained_variance_ratio_)

print(f"Cumulative Explained Variance: {cumulative_variance}")

# Plot cumulative explained variance
plt.figure(figsize=(8, 6))

plt.plot(
    range(1, len(cumulative_variance) + 1),
    cumulative_variance,
    marker='o'
)

plt.axhline(
    y=0.90,
    linestyle='--',
    label='90% Variance'
)

plt.axhline(
    y=0.95,
    linestyle='--',
    label='95% Variance'
)

plt.xlabel('Number of Principal Components')
plt.ylabel('Cumulative Explained Variance')
plt.title('Cumulative Explained Variance using PCA')
plt.legend()
plt.grid(True)

plt.show()

# Choose the number of components needed to capture
# at least 95% of the variance

n_components = np.argmax(cumulative_variance >= 0.95) + 1

print(f"Number of components selected: {n_components}")

pca = PCA(n_components=n_components)

X_train_pca = pca.fit_transform(X_train_scaled)

X_test_pca = pca.transform(X_test_scaled)

print(f"Original scaled training shape: {X_train_scaled.shape}")

print(f"PCA training shape: {X_train_pca.shape}")

print(f"Original scaled testing shape: {X_test_scaled.shape}")

print(f"PCA testing shape: {X_test_pca.shape}")

# Part E

def evaluate_model(clf, x_train_data, x_test_data, model_name, dataset_type):
    clf.fit(x_train_data, y_train)
    y_predict = clf.predict(x_test_data)

    accuracy = accuracy_score(y_test, y_predict)
    precision = precision_score(y_test, y_predict, zero_division=0)
    recall = recall_score(y_test, y_predict, zero_division=0)
    f1 = f1_score(y_test, y_predict, zero_division=0)

    print(model_name)
    print("Features used:", dataset_type)
    print("=" * 60)
    print(f"Accuracy:  {accuracy:.4f}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall:    {recall:.4f}")
    print(f"F1-score:  {f1:.4f}")

    print("\nConfusion Matrix:")
    print(confusion_matrix(y_test, y_predict))

    print("\nClassification Report:")
    print(classification_report(y_test, y_predict, target_names=['Bad Risk', 'Good Risk'], zero_division=0))

    return {
        'Model': model_name,
        'Features': dataset_type,
        'Accuracy': accuracy,
        'Precision': precision,
        'Recall': recall,
        'F1-score': f1
    }

# Display the results
results = [
    evaluate_model(LogisticRegression(max_iter=1000, random_state=42), X_train_scaled, X_test_scaled, 'Logistic Regression',
                   'Original Features'),
    evaluate_model(KNeighborsClassifier(n_neighbors=5), X_train_scaled, X_test_scaled, 'K-Nearest Neighbours',
                   'Original Features'),
    evaluate_model(DecisionTreeClassifier(random_state=42), X_train_scaled, X_test_scaled, 'Decision Tree',
                   'Original Features'),
    evaluate_model(LogisticRegression(max_iter=1000, random_state=42), X_train_pca, X_test_pca, 'Logistic Regression',
                   'PCA Features'),
    evaluate_model(KNeighborsClassifier(n_neighbors=5), X_train_pca, X_test_pca, 'K-Nearest Neighbours', 'PCA Features'),
    evaluate_model(DecisionTreeClassifier(random_state=42), X_train_pca, X_test_pca, 'Decision Tree', 'PCA Features')
]

results_df = pd.DataFrame(results)

print("Comparing the models")

print(results_df.to_string(index=False))

# Part F

# Choose the best model

best_result = results_df.loc[
    results_df['F1-score'].idxmax()
]

print("Best Model Before Tuning")
print("=" * 50)
print(best_result)

best_model_name = best_result['Model']
best_feature_type = best_result['Features']

print(f"Model selected for tuning: {best_model_name}")

print(f"Feature set selected: {best_feature_type}")

if best_feature_type == 'Original Features':

    X_train_best = X_train_scaled
    X_test_best = X_test_scaled

else:

    X_train_best = X_train_pca
    X_test_best = X_test_pca

if best_model_name == 'Logistic Regression':

    model = LogisticRegression(max_iter=1000)

    parameter_grid = {
        'C': [0.01, 0.1, 1, 10, 100],
        'solver': ['liblinear', 'lbfgs']
    }

elif best_model_name == 'K-Nearest Neighbours':

    model = KNeighborsClassifier()

    parameter_grid = {
        'n_neighbors': [3, 5, 7, 9, 11],
        'weights': ['uniform', 'distance'],
        'metric': ['euclidean', 'manhattan']
    }

# The Decision Tree Frid Search

else:

    model = DecisionTreeClassifier(random_state=42)

    parameter_grid = {
        'criterion': ['gini', 'entropy'],
        'max_depth': [None, 3, 5, 7, 10],
        'min_samples_split': [2, 5, 10],
        'min_samples_leaf': [1, 2, 5]
    }

# Apply the GridSearchCV

grid_search = GridSearchCV(
    estimator=model,
    param_grid=parameter_grid,
    cv=5,
    scoring='f1',
    n_jobs=-1
)

grid_search.fit(X_train_best,y_train)


print(f" The Best Parameters : {grid_search.best_params_}")

print(f"Best Cross-Validation F1-Score : {grid_search.best_score_}")

tuned_model = grid_search.best_estimator_

# Generate predictions on test data
y_predict_tuned = tuned_model.predict(X_test_best)

# Evaluation metrics (all updated to use y_predict_tuned)
tuned_accuracy = accuracy_score(
    y_test,
    y_predict_tuned
)

tuned_precision = precision_score(
    y_test,
    y_predict_tuned,
    zero_division=0
)

tuned_recall = recall_score(
    y_test,
    y_predict_tuned,
    zero_division=0
)

tuned_f1 = f1_score(
    y_test,
    y_predict_tuned,
    zero_division=0
)

# Display the tuned model results
print("The tuned model results")
print(f"Accuracy:  {tuned_accuracy:.4f}")
print(f"Precision: {tuned_precision:.4f}")
print(f"Recall:    {tuned_recall:.4f}")
print(f"F1-score:  {tuned_f1:.4f}")

print(f"Confusion Matrix:\n{confusion_matrix(y_test, y_predict_tuned)}")

print("Classification Report:")
print(
    classification_report(
        y_test,
        y_predict_tuned,
        target_names=['Bad', 'Good'],
        zero_division=0
    )
)

# Before and after comparison :

original_f1 = best_result['F1-score']

print("HyperParameter tuning before and after tuning ")

print(f"F1-score before tuning: {original_f1:.4f}")
print(f"F1-score after tuning:  {tuned_f1:.4f}")

if tuned_f1 > original_f1:
    print("The F1-score has improved after hyperparameter tuning.")

elif tuned_f1 < original_f1:
    print("The F1-score has decreased after hyperparameter tuning.")

else:
    print("The F1-score has remained the same after hyperparameter tuning.")

# Explanation of the bias and variance:

# Bias is an error that is  caused by a model being too simple.
#  High-bias models can underfit the training data and fail
# to capture important patterns.

# Variance is an  error caused by a model being too sensitive
# to the training data.
# A high-variance model can overfit the training data and perform
# poorly on unseen data.

# Hyperparameter tuning attempts to find a suitable balance
# between bias and variance.

# If the tuned model performs better on unseen test data,
# the selected hyperparameters may have improved the model's
# ability to generalise.

# If training performance is very high but test performance is
# much lower, this can indicate possible overfitting and high variance.

# If both the training and test performance are low, then this can indicate
# underfitting and high bias.


