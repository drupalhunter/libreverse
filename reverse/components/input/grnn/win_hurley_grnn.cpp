#include <cstdio>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cmath>
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <sstream>

#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
using namespace std;

#define MaxInstances 500
#define MaxAttributes 50
#define MaxDesiredOutputs 25

int main2(string, string, string, double);

double avg_distance;

class aSGRNN
{
  public:
    aSGRNN(){}
    aSGRNN(int Pts, int Ats, double T[][MaxAttributes], 
           double D[], double Sigma);

    void setNet(int Pts, int Ats, double T[][MaxAttributes], 
                double D[], double Sigma);

    double f(double X[MaxAttributes]);

  private:
    double hiddenFunction(double X[MaxAttributes], double T[MaxAttributes], 
                          double Sigma);
    double dist_squared(double X[MaxAttributes], double T[MaxAttributes]);

    double t[MaxInstances][MaxAttributes], 
           d[MaxInstances], 
           sigma;

    int    pts, ats;
};

aSGRNN::aSGRNN(int Pts, int Ats, double T[][MaxAttributes], double D[], double Sigma)
{
  setNet(Pts,Ats,T,D,Sigma);
}

void aSGRNN::setNet(int Pts, int Ats, double T[][MaxAttributes], double D[], double Sigma)
{
  int i, j;

  pts   = Pts;
  ats   = Ats;
  sigma = Sigma;

  for (i=0; i<pts; i++)
    {
      for (j=0; j<ats; j++)
        t[i][j] = T[i][j];
      d[i] = D[i];
    }
}

double aSGRNN::dist_squared(double X[MaxAttributes], double T[MaxAttributes])
{
  int i;
  double dist_sqr = 0;

  for (i=0; i<ats; i++)
    dist_sqr += pow((X[i]-T[i]),2.0); 

  return dist_sqr;
}


double aSGRNN::hiddenFunction(double X[MaxAttributes], double T[MaxAttributes], double Sigma)
{
  return exp(-dist_squared(X,T)/(2*pow(Sigma,2.0)));
}


double aSGRNN::f(double X[MaxAttributes])
{
  int i;
  double hf, weighted_sum_hfs= 0.0, 
         sum_hfs = 0.0;

  // From training list[0] -> training_list[pts]
  for (i=0; i<pts; i++)
    {
      hf = hiddenFunction(X,t[i],sigma);

      weighted_sum_hfs += hf * d[i];
      sum_hfs          += hf;
    }
 
  if (sum_hfs == 0)
    return 0;
  else    
    return weighted_sum_hfs/(sum_hfs);
}

int main(int argc, char *argv[])
{
	string train, test, out;
	double sigma = 0;
	
	  if (argc<5)
  {
    cout << "Must supply the program with <training set> <e/v/t test> <output file> <sigma>\n";
    exit(1);
  }
  
	train = argv[1];
	test = argv[2];
	out = argv[3];
	
  ifstream trainingData(argv[1]);
  ifstream testData(argv[2]);
  ofstream output(argv[3]);

  sigma =(double) atof(argv[4]);
  
  int best = 0, temp = 0, fitness = 0;
  double best_sigma = 0;
  
  double mys = 1;
  int lasti = 0, totali=0;
  double delta = 0.25;
  double s =1;
  double totalsig = 0, totaldist = 0, totalsuccess = 0;
  cout << mys;
  string best_s = " ";
  std::stringstream ss;
  std::string str;
  
  srand(time(NULL));
  double old_distance = 100;
  
  int i = 0;
for(int j=0; j<30;j++)
{
temp = 0;
fitness = 0;
best_sigma = 0;
best = 0;
i = 0;
mys = 1;
s = 1;
lasti = 0;

 while (i < 100)
 {
 i++;
 	//EHC code
	mys = s;
	mys = (rand()/(double)RAND_MAX)*mys*delta;
	
	temp = main2(train,test,out,mys);
	
	//if better, do this
	if(temp > fitness)
	{
	lasti = i;
	s = mys;
	fitness = temp;
	old_distance = avg_distance;
	cout << "Got a new s: " << s << " at iteration " << i << "fitness: " << fitness <<  " distance " << old_distance <<endl;
	}
	
	if(temp == fitness)
	{
		if(avg_distance < old_distance)
		{
		lasti = i;
		fitness = temp;
		s = mys;
		old_distance = avg_distance;
	cout << "Got a new s: " << s << " at iteration " << i << "fitness: " << fitness <<  " distance " << old_distance <<endl;
		}
	}
	
// 	temp = main2(train, test, out, s);
// 	
// 		if (temp == best)
// 		{
// 			if(avg_distance < old_distance)
// 			{
// 			best = temp;
// 			best_sigma = s;
// 			old_distance = avg_distance;
// 			}
// 		}
// 		
// 		if (temp > best)
// 		{
// 		best = temp;
// 		best_sigma = s;
// 		
// 		old_distance = avg_distance;
// 		}
		
  }
	
	cout << "Best success rate was: " << fitness << endl;
	cout << "Best sigma value was: " << s << endl;
	cout << "Best avg distance was: " << old_distance << endl;
	totali += lasti;
	totalsig += s;
	totaldist += old_distance;
	totalsuccess += fitness;
}
cout << "Average iterations to best solution: " << totali/30 << endl;
cout << "Average sigma discovered: " << totalsig/30 << endl;
cout << "Average average distance: " << totaldist/30 << endl;
cout << "Average success rate: " << totalsuccess/(double)30 << endl;
}


int main2(string tr, string ts, string o, double s)
{



  double x[MaxAttributes], result[MaxDesiredOutputs], 
         sigma[2],
         t[MaxInstances][MaxAttributes], 
         d[MaxDesiredOutputs][MaxInstances], desired_output[MaxDesiredOutputs],
         sum_sqr_err, temp;

  int i, j, k, trainingInstances, 
      testInstances, attributes, desiredOutputs;


  ifstream trainingData(tr.c_str() );
  ifstream testData(ts.c_str() );
  ofstream output(o.c_str());

  sigma[0] = s;
// sigma[1] = atof(argv[5]);

  output << "Files " << tr << " " << ts << endl;
  output << "Sigma " << s << endl;

//	cout << tr;
	
  trainingData >> trainingInstances >> attributes >> desiredOutputs;

  if (trainingInstances > MaxInstances)
    trainingInstances = MaxInstances;
  if (attributes > MaxAttributes)
    attributes = MaxAttributes;
  if (desiredOutputs > MaxDesiredOutputs)
    desiredOutputs = MaxDesiredOutputs;
  
  for (i=0; i<trainingInstances; i++)
  {
    for (j=0; j<attributes; j++)
      trainingData >> t[i][j];
    for (k=0; k<desiredOutputs; k++)
      trainingData >> d[k][i];
  }
  
  aSGRNN sgrnn;

  testData >> testInstances >> attributes >> desiredOutputs;
  
 //   cout << testInstances << attributes << desiredOutputs;

  if (testInstances > MaxInstances)
    testInstances = MaxInstances;
  if (attributes > MaxAttributes)
    attributes = MaxAttributes;
  if (desiredOutputs > MaxDesiredOutputs)
    desiredOutputs = MaxDesiredOutputs;

  sum_sqr_err = 0.0;

  int beginTime = time(NULL);
  int classError = 0;
  int correct = 0;
  double sum_error = 0.0;
  


  for (i=0; i<testInstances; i++)
  {

    double error[2], sum_temp = 0.0;
 
    for (j=0; j<attributes; j++)
      testData >> x[j];
    for (k=0; k<desiredOutputs; k++)
      testData >> desired_output[k];

    for (j=0; j<attributes; j++)
      output << x[j] << " ";
    output << ": ";
	 

		
    for (k=0; k<desiredOutputs; k++)
      output << desired_output[k] << " ";
    output << " : ";

    for (k=0; k<desiredOutputs; k++)
      {
        sgrnn.setNet(trainingInstances,attributes,t,d[k],sigma[k]);
        result[k] = sgrnn.f(x);
        output << result[k] << " "; 
        error[k] = pow((desired_output[k] - result[k]),2.0);
		  
		  //modification on 4/21/2007
		  if(fabs(desired_output[k] - result[k]) < 0.5)
		  	correct++;
        sum_sqr_err += error[k]; 
        sum_temp += error[k];
      }
    sum_error += sqrt(sum_temp);
    output << endl;
  }

  int endTime = time(NULL);

//   cout << "Correct classifications: " << correct << endl;
//   cout << "Average Error = " << sum_sqr_err/testInstances << endl;
//   cout << "Classification Error = " << classError/desiredOutputs/testInstances << endl;
// 
//   cout << "Average Evaluation Time = " << (float)(endTime-beginTime)/testInstances << endl;
  
  output << "Average Distance = " << sum_error/testInstances <<endl;

  trainingData.close();
  testData.close();
  output.close();

	avg_distance = sum_error/testInstances;
  return correct;
} 
