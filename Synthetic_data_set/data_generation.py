import numpy as np
import pandas as pd

# Generate synthetic data
np.random.seed(42)


def generate_data(n_samples=14000):
    data = []

    for _ in range(n_samples):
        rpm = np.random.normal(400, 60)  # RPM centered around 1150 with some noise
        vibration = np.random.normal(0.98, 0.08)  # Vibration centered around 0.98 with some noise
        current = np.random.normal(0.9, 0.1)  # Current centered around 0.8 with some noise

        # Determine condition based on the parameters
        if (380 <= rpm <= 450) and (0.9 <= vibration <= 1.06) and (0.8 <= current <= 1.8):
            condition = "Normal"
        else:
            condition = "Needs Maintenance"

        data.append([rpm, vibration, current, condition])

    df = pd.DataFrame(data, columns=['RPM', 'Vibration', 'Current', 'Condition'])
    return df


# Generate dataset
df = generate_data(5000)

# Save dataset to CSV
df.to_csv('fan_motor_dataset_new.csv', index=False)
print("Dataset generated and saved to 'fan_motor_dataset.csv'")
