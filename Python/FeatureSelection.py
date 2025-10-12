import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
from sklearn.tree import DecisionTreeClassifier, plot_tree
import matplotlib.pyplot as plt

# For forward/backward selection
from mlxtend.feature_selection import SequentialFeatureSelector as SFS

# --- Step 1: Create a toy dataset ---
np.random.seed(42)

n = 100
Hours_Studied = np.random.randint(0, 10, n)
Attendance = np.random.randint(50, 100, n)
Sleep = np.random.randint(4, 9, n)
Social_Media_Time = np.random.randint(0, 6, n)

# Simple rule: Pass depends on study hours and attendance
Pass = ((Hours_Studied > 4) & (Attendance > 70)).astype(int)

df = pd.DataFrame({
    'Hours_Studied': Hours_Studied,
    'Attendance': Attendance,
    'Sleep': Sleep,
    'Social_Media_Time': Social_Media_Time,
    'Pass': Pass
})

X = df.drop('Pass', axis=1)
y = df['Pass']

# --- Step 2: Forward Selection ---
log_reg = LogisticRegression(max_iter=1000)
sfs_forward = SFS(log_reg, 
                  k_features='best', 
                  forward=True, 
                  floating=False, 
                  scoring='accuracy', 
                  cv=5)
sfs_forward.fit(X, y)
print("Forward Selection result:", sfs_forward.k_feature_names_)

# --- Step 3: Backward Elimination ---
sfs_backward = SFS(log_reg, 
                   k_features='best', 
                   forward=False, 
                   floating=False, 
                   scoring='accuracy', 
                   cv=5)
sfs_backward.fit(X, y)
print("Backward Elimination result:", sfs_backward.k_feature_names_)

# --- Step 4: Decision Tree Induction ---
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
tree = DecisionTreeClassifier(max_depth=3, random_state=42)
tree.fit(X_train, y_train)

print("Decision Tree accuracy:", accuracy_score(y_test, tree.predict(X_test)))

# Plot the decision tree
plt.figure(figsize=(10,6))
plot_tree(tree, feature_names=X.columns, class_names=["Fail", "Pass"], filled=True)
plt.show()