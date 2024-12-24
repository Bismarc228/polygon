#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

double distance(double a, double b) {
    return fabs(a - b);
}

vector<double> kmeansPlusPlus(const vector<double>& points, int K) {
    vector<double> centroids;

    centroids.push_back(points[rand() % points.size()]);

    for (int i = 1; i < K; ++i) {
        vector<double> distances(points.size());
        double totalDistance = 0;

        for (size_t j = 0; j < points.size(); ++j) {
            double minDist = numeric_limits<double>::infinity();
            for (const auto centroid : centroids) {
                minDist = min(minDist, distance(points[j], centroid));
            }
            distances[j] = minDist * minDist;  // Квадрат расстояния
            totalDistance += distances[j];
        }

        // 3. Выбор следующего центроида с вероятностью, пропорциональной квадрату расстояния
        double randomVal = (rand() / static_cast<double>(RAND_MAX)) * totalDistance;
        double cumulativeSum = 0;
        for (size_t j = 0; j < points.size(); ++j) {
            cumulativeSum += distances[j];
            if (cumulativeSum >= randomVal) {
                centroids.push_back(points[j]);
                break;
            }
        }
    }

    return centroids;
}


void kmeans(const vector<double>& points, vector<double>& centroids, vector<vector<double>>& clusters, int maxIterations = 100) {
    vector<int> labels(points.size(), -1);
    int K = centroids.size();

    for (int iter = 0; iter < maxIterations; ++iter) {
        bool changed = false;
        for (size_t i = 0; i < points.size(); ++i) {
            int bestLabel = -1;
            double minDist = numeric_limits<double>::infinity();
            for (int j = 0; j < K; ++j) {
                double dist = distance(points[i], centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    bestLabel = j;
                }
            }
            if (labels[i] != bestLabel) {
                labels[i] = bestLabel;
                changed = true;
            }
        }

        if (!changed) break;

        vector<double> newCentroids(K, 0);
        vector<int> clusterSizes(K, 0);

        clusters.clear();
        clusters.resize(K);

        for (size_t i = 0; i < points.size(); ++i) {
            int cluster = labels[i];
            newCentroids[cluster] += points[i];
            clusterSizes[cluster]++;
            clusters[cluster].push_back(points[i]);  // Добавляем точку в соответствующий кластер
        }

        for (int j = 0; j < K; ++j) {
            if (clusterSizes[j] > 0) {
                newCentroids[j] /= clusterSizes[j];
            }
        }

        centroids = newCentroids;
    }
}

int main() {
    srand(time(0));
    vector<double> points = {1,2,3,11,22,33,12,13,41,24,26,35,34,37};
    int K = 4; // Количество кластеров

    // 1. Выбор начальных центроидов с использованием K-means++
    vector<double> centroids = kmeansPlusPlus(points, K);

    // Вектор для хранения кластеров
    vector<vector<double>> clusters(K);

    // 2. Запуск K-means с выбранными центроидами
    kmeans(points, centroids, clusters);

    // Выводим результаты
    cout << "Clusters:\n";
    for (int i = 0; i < K; ++i) {
        cout << "Cluster " << i + 1 << ": ";
        for (double point : clusters[i]) {
            cout << point << " ";
        }
        cout << endl;
    }
}
