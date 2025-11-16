import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("data.csv")

colors = {
    "quick": "black",
    "intro": "blue",
}

def plot_category(quick_col, intro_col, filename, title):
    plt.figure(figsize=(8, 5))

    plt.plot(data["N"], data[quick_col], label="QuickSort",
             color=colors["quick"], linewidth=2)

    plt.plot(data["N"], data[intro_col], label="IntroSort",
             color=colors["intro"], linewidth=2)

    plt.xlabel("Размер массива N")
    plt.ylabel("Время выполнения (мкс)")
    plt.title(title)
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.tight_layout()
    plt.savefig(filename, dpi=200)
    plt.close()


# random
plot_category(
    "quick_rand", "intro_rand",
    "plot_random.png",
    "Время работы сортировок (Random)"
)

# reversed
plot_category(
    "quick_reversed", "intro_reversed",
    "plot_reversed.png",
    "Время работы сортировок (Reversed)"
)

# almost sorted
plot_category(
    "quick_almost", "intro_almost",
    "plot_almost_sorted.png",
    "Время работы сортировок (Almost sorted)"
)

print("Все графики сохранены: plot_random.png, plot_reversed.png, plot_almost_sorted.png")
