import pandas as pd

# Tạo DataFrame từ dict
data = {
    "Tên": ["An", "Bình", "Chi"],
    "Tuổi": [23, 25, 22],
    "Điểm": [8.5, 7.0, 9.0]
}
df = pd.DataFrame(data)

print(df)
