#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath> // Include cmath to use sin

struct SensorData
{
    std::vector<double> xGyro, yGyro, zGyro;
    std::vector<double> xAccel, yAccel, zAccel;
};

SensorData read_txt_file(const std::string fileName);
SensorData read_ins_file(const std::string &fileName);
double calculateMean(const std::vector<double> &data);
std::pair<double, double> calculateBiasAndScaleAccel(double &upPosition, double &downPosition);
std::pair<double, double> calculateBiasAndScaleGyro(double &upPosition, double &downPosition);
// Function to print Bias and Scale for all axes
void printBiasAndScale(const std::string &label, const std::vector<std::pair<double, double>> &data);
std::pair<double, double> calculateVarianceAndStd(std::vector<double> data, double mean);
void printVarianceAndStd(const std::string &label, const std::vector<std::pair<double, double>> &data);

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

    // Calculate Bias and Scale for Gyros and Accelerometers
    std::vector<std::pair<double, double>> gyroBiasAndScale = {
        calculateBiasAndScaleGyro(meanUpGyroX, meanDownGyroX),
        calculateBiasAndScaleGyro(meanUpGyroY, meanDownGyroY),
        calculateBiasAndScaleGyro(meanUpGyroZ, meanDownGyroZ)};

    std::vector<std::pair<double, double>> accelBiasAndScale = {
        calculateBiasAndScaleAccel(meanUpAccelX, meanDownAccelX),
        calculateBiasAndScaleAccel(meanUpAccelY, meanDownAccelY),
        calculateBiasAndScaleAccel(meanUpAccelZ, meanDownAccelZ)};

    // Print Bias and Scale for Gyros and Accelerometers
    printBiasAndScale("Gyroscope", gyroBiasAndScale);
    printBiasAndScale("Accelerometer", accelBiasAndScale);
    // Reading INS FILES

    // Read the binary data for "up" and "down" positions
    SensorData dataUpINS = read_ins_file("x_LN100_up.ins");     // For "up"
    SensorData dataDownINS = read_ins_file("x_LN100_down.ins"); // For "down"

    // Mean Values for Gyros (INS)
    double meanUpGyroX_INS = calculateMean(dataUpINS.xGyro);
    double meanUpGyroY_INS = calculateMean(dataUpINS.yGyro);
    double meanUpGyroZ_INS = calculateMean(dataUpINS.zGyro);

    double meanDownGyroX_INS = calculateMean(dataDownINS.xGyro);
    double meanDownGyroY_INS = calculateMean(dataDownINS.yGyro);
    double meanDownGyroZ_INS = calculateMean(dataDownINS.zGyro);

    // Mean values for accelerometer (INS)
    double meanUpAccelX_INS = calculateMean(dataUpINS.xAccel);
    double meanUpAccelY_INS = calculateMean(dataUpINS.yAccel);
    double meanUpAccelZ_INS = calculateMean(dataUpINS.zAccel);

    double meanDownAccelX_INS = calculateMean(dataDownINS.xAccel);
    double meanDownAccelY_INS = calculateMean(dataDownINS.yAccel);
    double meanDownAccelZ_INS = calculateMean(dataDownINS.zAccel);

    // Calculate Bias and Scale for Gyros and Accelerometers (INS)
    std::vector<std::pair<double, double>> gyroBiasAndScale_INS = {
        calculateBiasAndScaleGyro(meanUpGyroX_INS, meanDownGyroX_INS),
        calculateBiasAndScaleGyro(meanUpGyroY_INS, meanDownGyroY_INS),
        calculateBiasAndScaleGyro(meanUpGyroZ_INS, meanDownGyroZ_INS)};

    std::vector<std::pair<double, double>> accelBiasAndScale_INS = {
        calculateBiasAndScaleAccel(meanUpAccelX_INS, meanDownAccelX_INS),
        calculateBiasAndScaleAccel(meanUpAccelY_INS, meanDownAccelY_INS),
        calculateBiasAndScaleAccel(meanUpAccelZ_INS, meanDownAccelZ_INS)};

    // Print Bias and Scale for Gyros and Accelerometers (INS)
    printBiasAndScale("Gyroscope (INS)", gyroBiasAndScale_INS);
    printBiasAndScale("Accelerometer (INS)", accelBiasAndScale_INS);

    // Part 2
    // Calculate variance

    // VARIANCE AND STANDARD DEVIATION OF  MEAN GYRO UP AND DOWN POSITIONS
    // std::pair<double, double> varianceAndMeanStdGyroUpX = calculateVarianceAndStd(data_up.xGyro, meanUpGyroX);
    // std::pair<double, double> varianceAndMeanStdGyroUpY = calculateVarianceAndStd(data_up.yGyro, meanUpGyroY);
    // std::pair<double, double> varianceAndMeanStdGyroUpZ = calculateVarianceAndStd(data_up.zGyro, meanUpGyroZ);

    // std::pair<double, double> varianceAndMeanStdGyroDownX = calculateVarianceAndStd(data_down.xGyro, meanDownGyroX);
    // std::pair<double, double> varianceAndMeanStdGyroDownY = calculateVarianceAndStd(data_down.yGyro, meanDownGyroY);
    // std::pair<double, double> varianceAndMeanStdGyroDownZ = calculateVarianceAndStd(data_down.zGyro, meanDownGyroZ);

    // VARIANCE AND STANDARD DEVIATION OF EAN ACCELEROMETER UP AND DOWN POSITIONS

    // std::pair<double, double> varianceAndMeanStdAccelUpX = calculateVarianceAndStd(data_up.xAccel, meanUpAccelX);
    // std::pair<double, double> varianceAndMeanStdAccelUpY = calculateVarianceAndStd(data_up.yAccel, meanUpAccelY);
    // std::pair<double, double> varianceAndMeanStdAccelUpZ = calculateVarianceAndStd(data_up.zAccel, meanUpAccelZ);

    // std::pair<double, double> varianceAndMeanStdAccelDownX = calculateVarianceAndStd(data_down.xAccel, meanDownAccelX);
    // std::pair<double, double> varianceAndMeanStdAccelDownY = calculateVarianceAndStd(data_down.yAccel, meanDownAccelY);
    // std::pair<double, double> varianceAndMeanStdAccelDownZ = calculateVarianceAndStd(data_down.zAccel, meanDownAccelZ);

    // Calculate Bias and Scale for Gyros Up Position
    std::vector<std::pair<double, double>> gyroUpVarianceMeanStd = {
        calculateVarianceAndStd(data_up.xGyro, meanUpGyroX),
        calculateVarianceAndStd(data_up.yGyro, meanUpGyroY),
        calculateVarianceAndStd(data_up.zGyro, meanUpGyroZ),
    };

    // Calculate Bias and Scale for Gyros Down Position
    std::vector<std::pair<double, double>> gyroDownVarianceMeanStd = {
        calculateVarianceAndStd(data_down.xGyro, meanDownGyroX),
        calculateVarianceAndStd(data_down.yGyro, meanDownGyroY),
        calculateVarianceAndStd(data_down.zGyro, meanDownGyroZ),
    };

    printVarianceAndStd("Gyroscope Up Position:", gyroUpVarianceMeanStd);
    printVarianceAndStd("Gyroscope Down Position:", gyroDownVarianceMeanStd);


    // Calculate Bias and Scale for Accelerometer Up Position
    std::vector<std::pair<double, double>> accelUpVarianceMeanStd = {
        calculateVarianceAndStd(data_up.xAccel, meanUpAccelX),
        calculateVarianceAndStd(data_up.yAccel, meanUpAccelY),
        calculateVarianceAndStd(data_up.zAccel, meanUpAccelZ),
    };

    // Calculate Bias and Scale for Accelerometer Down Position
    std::vector<std::pair<double, double>> accelDownVarianceMeanStd = {
        calculateVarianceAndStd(data_down.xAccel, meanDownAccelX),
        calculateVarianceAndStd(data_down.yAccel, meanDownAccelY),
        calculateVarianceAndStd(data_down.zAccel, meanDownAccelZ),
    };

    printVarianceAndStd("Accelerometer Up Position:", accelUpVarianceMeanStd);
    printVarianceAndStd("Accelerometer Down Position:", accelDownVarianceMeanStd);


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
        double time, xg, yg, zg, xa, ya, za;

        // Read the data from the binary file (assuming each value is a double)
        file.read(reinterpret_cast<char *>(&time), sizeof(double));
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

std::pair<double, double> calculateBiasAndScaleAccel(double &upPosition, double &downPosition)
{
    const double g = 9.80665;
    double bias = (upPosition + downPosition) / 2;
    double scale = (downPosition - upPosition - (2 * g)) / (2 * g);

    return std::make_pair(bias, scale);
}

// Function to calculate Bias and Scale for Gyros
std::pair<double, double> calculateBiasAndScaleGyro(double &upPosition, double &downPosition)
{
    // Earth’s rotation rate in deg/s (15 deg/hr to deg/s conversion)
    const double we = 15.041 / 3600.0;           // 15 degrees per hour -> degrees per second
    const double phi = 51.0755 * (M_PI / 180.0); // Latitude in radians (converted from degrees)

    // Calculate the bias
    double bias = (upPosition + downPosition) / 2;

    // Calculate the scale factor
    double scale = (downPosition - upPosition - (2 * we * sin(phi))) / (2 * we);
    // Return the bias and scale as a pair
    return std::make_pair(bias, scale);
}

void printBiasAndScale(const std::string &label, const std::vector<std::pair<double, double>> &data)
{
    std::cout << "********** " << label << " Calibration **********\n";
    std::cout << "Axis\tBias\t\tScale Factor\n";
    std::cout << "-------------------------------------\n";

    char axis[] = {'X', 'Y', 'Z'};
    for (int i = 0; i < 3; ++i)
    {
        std::cout << axis[i] << "\t" << data[i].first << "\t\t" << data[i].second << "\n";
    }
    std::cout << "-------------------------------------\n";
}

//
std::pair<double, double> calculateVarianceAndStd(std::vector<double> data, double mean)
{
    double vi = 0.0;
    for (double value : data)
    {
        vi += pow((value - mean), 2);
    }
    double variance = vi / (data.size() - 1);
    double standardDeviation = sqrt(variance);
    // standard deviations of the mean
    double standardDeviationMean = standardDeviation / sqrt(data.size());

    return std::make_pair(variance, standardDeviationMean);
}



void printVarianceAndStd(const std::string &label, const std::vector<std::pair<double, double>> &data)
{
    std::cout << "********** " << label << " **********\n";
    std::cout << "Axis\tVariance\t\tMean Standard Deviation \n";
    std::cout << "-------------------------------------\n";

    char axis[] = {'X', 'Y', 'Z'};
    for (int i = 0; i < 3; ++i)
    {
        std::cout << axis[i] << "\t" << data[i].first << "\t\t" << data[i].second << "\n";
    }
    std::cout << "-------------------------------------\n";
}