#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Simulation parameters
const double RTT = 0.1;          // seconds
const double SIM_TIME = 20.0;    // seconds
const int STEPS = (int)(SIM_TIME / RTT);

struct Result {
    double time[STEPS];
    double cwnd[STEPS];
    double throughput;
};

Result simulate_tcp_reno(double loss_prob) {
    Result r;

    double cwnd = 1.0;
    double ssthresh = 1000.0;
    double total_data = 0.0;

    srand(1); // fixed seed for stable runs

    for (int i = 0; i < STEPS; i++) {
        double t = i * RTT;

        r.time[i] = t;
        r.cwnd[i] = cwnd;

        total_data += cwnd;

        // random packet loss event
        double x = (double)rand() / RAND_MAX;
        bool loss = (x < loss_prob);

        if (loss) {
            // Multiplicative Decrease
            ssthresh = cwnd / 2.0;
            if (ssthresh < 1.0) ssthresh = 1.0;
            cwnd = ssthresh;
        } else {
            // Normal cwnd increase
            if (cwnd < ssthresh)
                cwnd *= 2.0;   // Slow Start
            else
                cwnd += 1.0;   // Congestion Avoidance
        }
    }

    r.throughput = total_data / SIM_TIME;
    return r;
}

void save_csv(Result r, const char* filename) {
    ofstream file(filename);
    file << "time,cwnd\n";
    for (int i = 0; i < STEPS; i++) {
        file << r.time[i] << "," << r.cwnd[i] << "\n";
    }
    file.close();
}

int main() {
    double losses[3] = {0.001, 0.01, 0.02};

    for (int i = 0; i < 3; i++) {
        double loss = losses[i];
        Result r = simulate_tcp_reno(loss);

        char filename[50];
        sprintf(filename, "cwnd_loss_%.3f.csv", loss);

        save_csv(r, filename);

        cout << "----------------------------------\n";
        cout << "Loss Rate: " << loss * 100 << "%\n";
        cout << "Average Throughput: " << r.throughput << " MSS/sec\n";
        cout << "Saved: " << filename << "\n";
    }

    cout << "\nSimulation complete. CSV files generated.\n";

    return 0;
}

