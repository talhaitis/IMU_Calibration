#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct SensorData
{
    std::vector<double> xGyro, yGyro, zGyro;
    std::vector<double> xAccel, yAccel, zAccel;
};

SensorData read_txt_file(const std::string fileName);
SensorData read_ins_file(const std::string &fileName);
double calculateMean(const std::vector<double> &data);
std::pair<double, double> calculateBiasAndScale(double &upPosition, double &downPosition);

int main()
{
    // Read the data for "up" position
    SensorData data_up = read_txt_file("x_adi_up.txt");

    // Read the data for "down" position
    SensorData data_down = read_txt_file("x_adi_down.txt");

    // Mean Values for Gyros
    double meanUpGyroX = calculateMean(data_up.xGyro);
    double meanUpGyroY = calculateMean(data_up.yGyro);
    double meanUpGyroZ = calculateMean(data_up.zGyro);

    double meanDownGyroX = calculateMean(data_down.xGyro);
    double meanDownGyroY = calculateMean(data_down.yGyro);
    double meanDownGyroZ = calculateMean(data_down.zGyro);

    // Mean values for accelerometer
    double meanUpAccelX = calculateMean(data_up.xAccel);
    double meanUpAccelY = calculateMean(data_up.yAccel);
    double meanUpAccelZ = calculateMean(data_up.zAccel);

    double meanDownAccelX = calculateMean(data_down.xAccel);
    double meanDownAccelY = calculateMean(data_down.yAccel);
    double meanDownAccelZ = calculateMean(data_down.zAccel);

    // Now calculate the mean for "up" and "down" separately using calculateMean()

    std::cout << "Up Position:\n";
    std::cout << "Gyro Mean: " << meanUpGyroX << ", " << meanUpGyroY << ", " << meanUpGyroZ << "\n";
    std::cout << "Accel Mean: " << meanUpAccelX << ", " << meanUpAccelY << ", " << meanUpAccelZ << "\n";

    std::cout << "Down Position:" << "\n";
    std::cout << "Gyro Mean: " << meanDownGyroX << ", " << meanDownGyroY << ", " << meanDownGyroZ << "\n";
    std::cout << "Accel Mean: " << meanDownAccelX << ", " << meanDownAccelY << ", " << meanDownAccelZ << "\n";

    // Bias and Scale in Gyros
    std::pair<double, double> biasAndScaleGyroX = calculateBiasAndScale(meanUpGyroX, meanDownGyroX);
    std::pair<double, double> biasAndScaleGyroY = calculateBiasAndScale(meanUpGyroY, meanDownGyroY);
    std::pair<double, double> biasAndScaleGyroZ = calculateBiasAndScale(meanUpGyroZ, meanDownGyroZ);

    // Bias and Scale in Accelerometer
    std::pair<double, double> biasAndScaleAccelX = calculateBiasAndScale(meanUpAccelX, meanDownAccelX);
    std::pair<double, double> biasAndScaleAccelY = calculateBiasAndScale(meanUpAccelY, meanDownAccelY);
    std::pair<double, double> biasAndScaleAccelZ = calculateBiasAndScale(meanUpAccelZ, meanDownAccelZ);

    // Bias in gyro &  accelerometer
    std::cout << "********************************" << "\n";
    std::cout << "****** Estimated Bias in Gyro's Axis *******" << "\n";
    std::cout << "X : " << biasAndScaleGyroX.first << "\n";
    std::cout << "Y : " << biasAndScaleGyroY.first << "\n";
    std::cout << "Z : " << biasAndScaleGyroZ.first << "\n";

    std::cout << "********************************" << "\n";
    std::cout << "****** Estimated Bias in Accelerometer's Axis *******" << "\n";
    std::cout << "X : " << biasAndScaleAccelX.first << "\n";
    std::cout << "Y : " << biasAndScaleAccelY.first << "\n";
    std::cout << "Z : " << biasAndScaleAccelZ.first << "\n";

    // Scale in gyro & accelerometer
    std::cout << "********************************" << "\n";
    std::cout << "****** Estimated Scale in Gyro's Axis *******" << "\n";
    std::cout << "X : " << biasAndScaleGyroX.second << "\n";
    std::cout << "Y : " << biasAndScaleGyroY.second << "\n";
    std::cout << "Z : " << biasAndScaleGyroZ.second << "\n";

    std::cout << "********************************" << "\n";
    std::cout << "****** Estimated Scale in Accelerometer's Axis *******" << "\n";
    std::cout << "X : " << biasAndScaleAccelX.second << "\n";
    std::cout << "Y : " << biasAndScaleAccelY.second << "\n";
    std::cout << "Z : " << biasAndScaleAccelZ.second << "\n";

    // Reading INS FILES

    // Read the binary data for "up" and "down" positions
    SensorData dataUpINS = read_ins_file("x_LN100_up.ins");     // For "up"
    SensorData dataDownINS = read_ins_file("x_LN100_down.ins"); // For "down"

    return 0;
}

SensorData read_txt_file(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << "\n";
        return {}; // return an empty struct if file couldn't be opened
    }

    SensorData data; // Struct to hold the gyro and accel data

    std::string line;
    while (getline(file, line))
    {
        double time, xg, yg, zg, xa, ya, za;

        // Parse the data using sscanf
        sscanf(line.c_str(), "%lf %lf %lf %lf %lf %lf %lf", &time, &xg, &yg, &zg, &xa, &ya, &za);

        // Store data in the respective vectors
        data.xGyro.push_back(xg);
        data.yGyro.push_back(yg);
        data.zGyro.push_back(zg);

        data.xAccel.push_back(xa);
        data.yAccel.push_back(ya);
        data.zAccel.push_back(za);
    }

    file.close();
    return data; // Return the struct containing the data
}

SensorData read_ins_file(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << "\n";
        return {}; // return an empty struct if file couldn't be opened
    }

    SensorData data; // Struct to hold the gyro and accel data

    // Read data until end of file
    while (file)
    {
        double xg, yg, zg, xa, ya, za;

        // Read the data from the binary file (assuming each value is a double)
        file.read(reinterpret_cast<char *>(&xg), sizeof(double));
        file.read(reinterpret_cast<char *>(&yg), sizeof(double));
        file.read(reinterpret_cast<char *>(&zg), sizeof(double));
        file.read(reinterpret_cast<char *>(&xa), sizeof(double));
        file.read(reinterpret_cast<char *>(&ya), sizeof(double));
        file.read(reinterpret_cast<char *>(&za), sizeof(double));

        if (file)
        { // Check if data was read successfully
            data.xGyro.push_back(xg);
            data.yGyro.push_back(yg);
            data.zGyro.push_back(zg);

            data.xAccel.push_back(xa);
            data.yAccel.push_back(ya);
            data.zAccel.push_back(za);
        }
    }

    file.close();
    return data; // Return the struct containing the data
}

double calculateMean(const std::vector<double> &data)
{
    double sum = 0.0;

    for (double value : data)
    {
        sum += value;
    }
    return sum / data.size();
}

std::pair<double, double> calculateBiasAndScale(double &upPosition, double &downPosition)
{
    const double g = 9.80665;
    double bias = (upPosition + downPosition) / 2;
    double scale = (downPosition - upPosition - (2 * g)) / (2 * g);

    return std::make_pair(bias, scale);
}