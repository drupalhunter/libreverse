/*  Forensics_GRNN.cpp

   Copyright (C) 2008 Stephen Torri

   This file is part of Libreverse.

   Libreverse is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   Libreverse is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

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

    class Optimizer
   {
   public:
      Optimizer(string tr, string te, string o);  
      double EHC(double sigma, double delta, int iter);
      double log(int iterations, double lb, double ub, int steps);
   
   private:
      string train;
      string test;
      string out;
      
   
   };
	
	//constructor
    Optimizer::Optimizer(string tr, string te, string o)
   {
      train = tr;
      test = te;
      out = o;
   }
   
	//log-based optimization
    double Optimizer::log(int iterations, double lb, double ub, int steps)
   {
      int i = 0;
      double range = ub - lb;
      double step_size = range/steps;
      int temp = 0;
      int best_fitness = 0;
      double best_sigma = 0;
      double current_sigma = 0;
   
      while (i < iterations)
      {
         
         best_fitness = 0;
      	
      //test for each step from the current lb to the current ub
         for (int k = 0; k <= steps; k++)
         {
            i++;
            current_sigma = k*step_size+lb;
            temp = main2(train,test,out,current_sigma);
            
         	//update best_fitness, best_sigma since a better value was found
            if(temp > best_fitness)
            {
               best_fitness = temp;
               best_sigma = current_sigma;
               
               cout << "New fitness: " << temp << endl;
               cout << "Sigma: " << current_sigma << endl;
               cout << "Function evaluations: " << i << " Steps: " << k << endl << endl;
            }
         }
         
      	//update lb, ub, range
         if(best_sigma != lb)
            lb = best_sigma - step_size;
         if(best_sigma != ub)
            ub = best_sigma + step_size;
            
         range = ub - lb;
         step_size = range/steps;
      	
      	
      }
   	
   	cout << "Testing on new data with sigma: " << best_sigma << endl;
   	cout << "Raw fitness is: " << main2(train,"test.txt","final.txt",best_sigma);
      return 0.0;
   }

	
	//sigma is the starting value of sigma, delta is the mutation amount, iter is the number
	//of iterations until termination
    double Optimizer::EHC(double sigma, double delta, int iter)
   {
      double temp_sigma = 0, current_sigma = sigma;
      double old_distance = 1000.0;
      double x = 0;
      int temp = 0, fitness = 0;
      int best_i = 0;
   	int k = 0;
   	double sum = 0;
   	
   while (k < 30) //for statistical sig
   {
   
   temp_sigma = 0;
   current_sigma= sigma;
   old_distance = 1000.0;
   x = 0;
   temp = 0;
   fitness = 0;
   best_i = 0;
   
      for (int i = 0 ; i < iter ; i++)
      {
          
         x = rand()/(double)RAND_MAX;
         //	cout << "x " <<  x << endl;
         //this line reverts to EHC mode
         if(x > 0.5)
         {
         //perform mutation
            temp_sigma = current_sigma + (rand()/(double)RAND_MAX)*current_sigma*delta;
            //cout << "mys " << mys << endl;
         }
         else
         {
            temp_sigma = current_sigma - (rand()/(double)RAND_MAX)*current_sigma*delta;
            if(temp_sigma < 0)
               temp_sigma = -1 * temp_sigma;
            //	cout << "mys " << mys << endl;
         }
      	
         temp = main2(train,test,out,temp_sigma);
         
         //if better, do this
         if(temp > fitness)
         {
            best_i = i;
            current_sigma = temp_sigma;
            fitness = temp;
            old_distance = avg_distance;
            //cout << "New fitness: " << fitness << endl;
            //cout << "Sigma: " << current_sigma << endl;
            //cout << "Iteration number: " << i << endl << endl;
            //	cout << "Got a new s: " << s << " at iteration " << i << "fitness: " << fitness <<  " distance " << old_distance <<endl;
         }
         
         if(temp == fitness)
         {
            if(avg_distance < old_distance)
            {
               //best_i = i;
               fitness = temp;
               current_sigma = temp_sigma;
               old_distance = avg_distance;
               //cout << "New fitness: " << fitness << endl;
               //cout << "Sigma: " << current_sigma << endl;
               //cout << "Iteration number: " << i << endl << endl;
               //	cout << "Got a new s: " << s << " at iteration " << i << "fitness: " << fitness <<  " distance " << old_distance <<endl;
            }
         }
      }
      
   	k++;
   	sum+=best_i;
   	cout << "Run " << k << endl << " Testing on new data with sigma: " << current_sigma << endl;
   	cout << "Raw fitness is: " << main2(train,"test.txt","final.txt",current_sigma);
   	
   	}
   	
   	cout << endl <<  "Average i: " << sum/30.0 << endl;
   }

    int main(int argc, char *argv[])
   {
      string train, test, out;
      int iterations = 0;
      int search_method = 0;
      double sigma = 0;
      
   	srand(time(NULL));
   
      if (argc<7)
      {
         cout << "Must supply the program with <training set> <e/v/t test> <output file> <sigma> <i><search>\n";
         exit(1);
      }
   
      train = argv[1];
      test = argv[2];
      out = argv[3];
      sigma =(double) atof(argv[4]);
      iterations = atoi(argv[5]);
      search_method = atoi(argv[6]);
   	
      Optimizer love(train, test, out);
   	
      //love.EHC(sigma,0.25,iterations);
   	
   	if(search_method == 0)
   	{
      love.log(iterations, 0, 1.0, 200);
      }
   	else
   	{
   	love.EHC(sigma,0.5,iterations);
   	}
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
   
      //cout << "Correct classifications: " << correct << endl;
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
