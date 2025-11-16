import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("data.csv")

colors = {
    "merge": "black",
    "merge_insertion_15": "blue",
    "merge_insertion_30": "green",
    "merge_insertion_50": "orange",
}

def plot_category(category_name, merge_col, cols_with_thresholds, filename, title):
    plt.figure(figsize=(8, 5))

    plt.plot(data["N"], data[merge_col], label="MergeSort", color=colors["merge"], linewidth=2)
    for col, label, color in zip(cols_with_thresholds,
                                 ["Merge+Insertion(15)", "Merge+Insertion(30)", "Merge+Insertion(50)"],
                                 [colors["merge_insertion_15"], colors["merge_insertion_30"], colors["merge_insertion_50"]]):
        plt.plot(data["N"], data[col], label=label, alpha=0.8, linewidth=1.8, color=color)

    plt.xlabel("Размер массива N")
    plt.ylabel("Время выполнения (мкс)")
    plt.title(title)
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.tight_layout()
    plt.savefig(filename, dpi=200)
    plt.close()


# Случайные массивы
plot_category(
    "random",
    "merge_rand",
    ["merge_insertion_15_rand", "merge_insertion_30_rand", "merge_insertion_50_rand"],
    "plot_random.png",
    "Время работы сортировок (Random)"
)

# Обратные массивы
plot_category(
    "reversed",
    "merge_reversed",
    ["merge_insertion_15_reversed", "merge_insertion_30_reversed", "merge_insertion_50_reversed"],
    "plot_reversed.png",
    "Время работы сортировок (Reversed)"
)

# Почти отсортированные
plot_category(
    "almost_sorted",
    "merge_almost_sorted",
    ["merge_insertion_15_almost_sorted", "merge_insertion_30_almost_sorted", "merge_insertion_50_almost_sorted"],
    "plot_almost_sorted.png",
    "Время работы сортировок (Almost sorted)"
)

print("Все графики сохранены: plot_random.png, plot_reversed.png, plot_almost_sorted.png")