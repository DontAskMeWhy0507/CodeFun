from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
import numpy as np
import math

# --------------------------
# 1️⃣ Load dữ liệu
# --------------------------
data = load_iris()
X = data.data
y = data.target

# Tách tập huấn luyện / kiểm tra
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# --------------------------
# 2️⃣ Cây với Information Gain (Entropy)
# --------------------------
clf_entropy = DecisionTreeClassifier(criterion='entropy', random_state=42)
clf_entropy.fit(X_train, y_train)
acc_entropy = clf_entropy.score(X_test, y_test)

# --------------------------
# 3️⃣ Cây với Gini Index
# --------------------------
clf_gini = DecisionTreeClassifier(criterion='gini', random_state=42)
clf_gini.fit(X_train, y_train)
acc_gini = clf_gini.score(X_test, y_test)

# --------------------------
# 4️⃣ Cây với Gain Ratio (tự cài đặt đơn giản)
# --------------------------

def entropy(y):
    """Tính entropy của tập nhãn y"""
    values, counts = np.unique(y, return_counts=True)
    probs = counts / len(y)
    return -np.sum(probs * np.log2(probs + 1e-9))

def information_gain_ratio(X, y, feature_index):
    """Tính Gain Ratio cho một thuộc tính"""
    total_entropy = entropy(y)
    values, counts = np.unique(X[:, feature_index], return_counts=True)
    weighted_entropy = 0
    split_info = 0

    for v, count in zip(values, counts):
        subset_y = y[X[:, feature_index] == v]
        p = count / len(y)
        weighted_entropy += p * entropy(subset_y)
        split_info -= p * np.log2(p + 1e-9)

    info_gain = total_entropy - weighted_entropy
    if split_info == 0:
        return 0
    return info_gain / split_info  # Gain Ratio

# Chọn đặc trưng có Gain Ratio cao nhất
ratios = [information_gain_ratio(X_train, y_train, i) for i in range(X_train.shape[1])]
best_feature = np.argmax(ratios)

print(f"Feature có Gain Ratio cao nhất: {data.feature_names[best_feature]} ({ratios[best_feature]:.4f})")

# Để minh họa, ta huấn luyện cây entropy nhưng ưu tiên feature này
clf_gainratio = DecisionTreeClassifier(criterion='entropy', random_state=42, max_depth=3)
clf_gainratio.fit(X_train[:, [best_feature]], y_train)
acc_gainratio = clf_gainratio.score(X_test[:, [best_feature]], y_test)

# --------------------------
# 5️⃣ So sánh kết quả
# --------------------------
print("\n=== KẾT QUẢ ===")
print(f"Information Gain (Entropy): {acc_entropy:.4f}")
print(f"Gini Index: {acc_gini:.4f}")
print(f"Gain Ratio (thủ công, 1 feature tốt nhất): {acc_gainratio:.4f}")
