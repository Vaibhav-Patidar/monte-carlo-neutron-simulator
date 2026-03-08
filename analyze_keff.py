import numpy as np
import matplotlib.pyplot as plt

# Load data from CSV
data = np.loadtxt("k_results.csv", skiprows=1)

# Compute statistics
mean_keff = np.mean(data)
std_keff = np.std(data)
min_keff = np.min(data)
max_keff = np.max(data)

print("Total simulations:", len(data))
print("Mean k_eff:", mean_keff)
print("Standard deviation:", std_keff)
print("Minimum k_eff:", min_keff)
print("Maximum k_eff:", max_keff)

# Plot histogram
plt.figure(figsize=(10,6))

plt.hist(data, bins=50)

# Draw vertical line for mean
plt.axvline(mean_keff, linestyle="dashed", linewidth=2)

plt.xlabel("k_eff")
plt.ylabel("Frequency")
plt.title("Distribution of Neutron Multiplication Factor (k_eff)")

# Show grid for readability
plt.grid(True)

# Save figure
plt.savefig("keff_histogram.png")

# Show plot
plt.show()