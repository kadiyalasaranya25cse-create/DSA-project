import pandas as pd
from sklearn.linear_model import LinearRegression

# Read CSV file created by C
data = pd.read_csv("sales.csv")

print("\n===== AI DEMAND FORECASTING =====")

# Previous six months
months = [[1], [2], [3], [4], [5], [6]]

for index, row in data.iterrows():

    sales = [
        row["m1"],
        row["m2"],
        row["m3"],
        row["m4"],
        row["m5"],
        row["m6"]
    ]

    # Create and train AI model
    model = LinearRegression()
    model.fit(months, sales)

    # Predict seventh month
    prediction = model.predict([[7]])

    demand = max(0, round(prediction[0]))

    stock = int(row["stock"])

    # Calculate required stock
    required = max(0, demand - stock)

    print("\nProduct ID:", row["id"])
    print("Product Name:", row["name"])
    print("Current Stock:", stock)
    print("Predicted Demand:", demand)

    if required > 0:
        print("Recommended Additional Stock:", required)
        print("Status: Reorder Recommended")
    else:
        print("Recommended Additional Stock: 0")
        print("Status: Sufficient Stock")