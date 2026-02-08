import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("hll_results.csv")

upper = df["mean_estimate"] + df["std"]
lower = df["mean_estimate"] - df["std"]

plt.figure(figsize=(10, 6))
plt.plot(df["step"], df["mean_estimate"], label="E(Nt)")
plt.fill_between(df["step"], lower, upper, alpha=0.3, label="±σ")

plt.xlabel("Processed stream size")
plt.ylabel("Estimated number of unique elements")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
