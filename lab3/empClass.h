#include "MixClass.h"

class Empirical
{
private:
	vector<double> x_s;
	vector<double> f_s;
	int n = 0;
	int k = 0;
public:
    Empirical(Standart &std, int n0 = 2, int k0 = 3);
    Empirical(Mixture &mix, int n0 = 2, int k0 = 3);
    Empirical(Empirical& emp);
    Empirical(int n0 = 2, int k0 = 3);
    Empirical(vector<double> x_s);
    ~Empirical();
    void set_n(int newN);
    void set_k(int newK);
    int get_n();
    int get_k();
    vector<double> get_x_s();
    vector<double> get_f_s();
    Empirical& operator=(const Empirical& emp);
    vector<double> generate_f_s();
    void result_to_file_empirical(int mod);
    double delta_calc(const double min, const double max);
    vector<double> create_intervals(const double delta, const double min, const double max);
    int get_interval_index(const vector<double>& intervals, const double x);
    double empirical_density(const double x);
    double math_expectation();
    double dispersion(); 
    double asymmetry();  
    double EmpExcess();
    vector<double> random_sample_simulation();
    double random_var_simulation();
    void save(string filename);
    void load(string filename);
};