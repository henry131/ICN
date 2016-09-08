#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

// Uniform link delay
const int delay_ms = 1;

//Function to create string for node to node connection
string insert (int a, int b) {
	string str;
	str.append("node[");
	str.append(SSTR(a));
	str.append("].face++ <--> { delay = ");
	str.append(SSTR(delay_ms));
	str.append("ms; } <-->node[");
	str.append(SSTR(b));
	str.append("].face++;");
	return str;

}

int main (int argc, char *argv[]) {

  int levels = 0;

  // No arguments / too many arguments passed - default for scenario A
  if (argc != 2)
  {
  // assume levels == 4
    levels = 4; 
  }
  else
  {
    levels = atoi(argv[1]);
    if (levels < 3 || levels > 8)
    {
      cerr << "Invalid levels value: expect between 3 and 8 inc." << endl;
	    exit(1);
    }
    
  }
   
  // Used later for probabilistic linking  
  double possible_links = 0;
	for (int i = 1; i < (levels-1); i++)
	{
	  possible_links += pow(3,i) * 2;
	}

	//initialise random seed
	srand (time(NULL));
  
  //Default (scenario A) has p granularity of 0.1 steps
  int u_size = 11;
  int r_size = 20;
  string u[] = {"00","01","02","03","04","05","06","07","08","09","10"};
  
  //If not default -> just doing p == 0 and p == 1
  //only need one repeat since no probabilistic element (none or all)
  if (levels != 4)
  {
    u_size = 2;
    r_size = 1;
	  u[1] = "10";
	}
  
  //PREPARE FOR FILE CREATION ETC.

	int number_of_nodes = 0;
	for (int i = 0; i < levels; i++)
	{
	  number_of_nodes += pow(3,i);
	}
	
	int num_clients = pow(3,(levels-1));
	
	string node_clients[num_clients];
	for (int i = 0; i < num_clients; i++)
	{
	  node_clients[i] = SSTR(number_of_nodes - 1 - i);
	}
	
	string r[r_size];
	for (int i = 1; i <= r_size; i++)
	{
		r[i-1] = SSTR(i);
	}

  //CREATE EACH FILE

	for (int i = 0; i < u_size; i++) {
		for (int j = 0; j < r_size; j++) {
			string network;
			network.append("tree_");
			network.append(SSTR(levels));
			network.append("_3_u");
			network.append(u[i]);
			network.append("_r");
			network.append(r[j]);
	
	    		string file_name = ("../../networks/");
			//string file_name = ("trees/");
			file_name.append(network);
			file_name.append(".ned");

			char * writable = new char[file_name.size() + 1];
			copy(file_name.begin(), file_name.end(), writable);
			writable[file_name.size()] = '\0';
	
			ofstream myfile;
			myfile.open (writable);
			if (myfile.is_open()){
				myfile 	<< "package networks;" << endl
								<< "network " + network + "_network extends base_network{" << endl
								<< endl
								<< "parameters:" << endl
								<< "//Number of ccn nodes" << endl
								<< "n = " + SSTR(number_of_nodes) + "; " << endl
								<< "//Number of repositories" << endl
								<< "node_repos = \"0\";" << endl
								<< "num_repos = 1;" << endl
								<< "replicas = 1;" << endl
						  	<< "//Number of clients" << endl
								<< "num_clients = " + SSTR(num_clients) + "; " << endl
								<< "node_clients = \"";
        for (int l = 0; l < num_clients; l++)
        {
         myfile << node_clients[l];
         if ((l + 1) != num_clients) myfile << ",";
        }
				myfile  << "\";" << endl
								<< endl
								<< "connections allowunconnected:" << endl
								<< endl
								<< "//Tree core" << endl;
								
				for (int k = 1; k < number_of_nodes; k++)
				{
					myfile << insert((k-1)/3,k) << endl;
				} 
							
				myfile << "//Uncle-Nephew - Aunt-Niece Connections" << endl;
			
				double percentage_of_connections = atoi(u[i].c_str())/10.0;
				if (percentage_of_connections > 1)
				{
					cerr << "Error with percentage from u" << endl;
					return 1;
				}
				
				double no_of_connections =  possible_links * percentage_of_connections;

				int high = number_of_nodes - 2;
				int low = 4;
				set <int> branched;
			
				for (int i = 0; i < no_of_connections; i++)
				{
					int a = rand() % ( high - low + 1 ) + low;
					int b;
					if (a >= low && a <= high)
					{
						int parent = (a-1)/3;
						int branch = a%3;
						if (branch == 0) branch = 3;
						branch = parent + branch - (parent % 3 == 0? 3:parent % 3);
						if (parent == branch || branched.count(a) != 0)
						{
							i--;
							continue;
						} else
						{
							branched.insert(a);
							b = branch;
						}			
					} else
					{
						cerr << "Created random number outside range" << endl;
					}
					myfile 	<< insert (b,a) << endl;
				} 							
			
				myfile << "}" << endl;
				cout << "Finished making " + network << endl;							
			} else
			{
				cerr << "Unable to open file";
			}
			// free the string after finished using it
			
			delete[] writable;
			// close file
			myfile.close();
		}
	}
	
	return 0;
}
