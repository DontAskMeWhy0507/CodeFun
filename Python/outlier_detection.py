import pandas as pd

# Sample dataset
data = {'age': [25, 27, 29, 31, 30, 28, 26, 27, 95, 29, 30, 28, 27, 26]}
df = pd.DataFrame(data)

# Calculate Q1, Q3, and IQR
Q1 = df['age'].quantile(0.25)
Q3 = df['age'].quantile(0.75)
IQR = Q3 - Q1

# Define bounds
lower_bound = Q1 - 1.5 * IQR
upper_bound = Q3 + 1.5 * IQR

# Detect outliers
df['is_outlier'] = (df['age'] < lower_bound) | (df['age'] > upper_bound)

print("Q1:", Q1)
print("Q3:", Q3)
print("IQR:", IQR)
print("Lower bound:", lower_bound)
print("Upper bound:", upper_bound)
print("\nData with outlier flag:\n", df)
