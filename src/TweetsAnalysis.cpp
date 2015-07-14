#include "header.h"



int main(int argc)
{
	
	multiset <int> uniqueWordsList;
	multiset<int>::iterator Median;
	double medianValue;

	clock_t start_m1 = clock();
	map<string, long int> tweets;
	map<string, long int> singleTweet;
	string line, word;
	int uniqueWordCount = 0, tempMedian = 0, medianPostion = 0;
	ifstream inputfile("tweet_input/tweets.txt");
	ofstream feature1OutputFile("tweet_output/ft1.txt");
	ofstream feature2OutputFile("tweet_output/ft2.txt");

	if (inputfile.is_open())
	{
		while (getline(inputfile, line))
		{
			istringstream iss(line);
			uniqueWordCount = 0;
			while (iss >> word) {
				tweets[word]++;
				singleTweet[word]++;
				if (singleTweet[word] == 1)
					uniqueWordCount++;

			}
			//The 1st line so median is 1st element
			if (uniqueWordsList.size() == 0)
			{
				uniqueWordsList.insert(uniqueWordCount);
				Median = uniqueWordsList.begin();
				medianValue = *Median;
				medianPostion++;

			}
			else
			{
				uniqueWordsList.insert(uniqueWordCount);
				if (uniqueWordCount < *Median)
					medianPostion++;

				if (uniqueWordsList.size() % 2 == 1)
				{
					if ((uniqueWordsList.size() / 2 + 1) < medianPostion)
					{
						medianPostion--;
						Median--;
					}
					else if ((uniqueWordsList.size() / 2 + 1) > medianPostion)
					{
						medianPostion++;
						Median++;
					}

					medianValue = *Median;

				}
				else
				{

					tempMedian = *Median;

					if (uniqueWordCount > *Median)
					{

						medianValue = ((double)*++Median + (double)tempMedian) / 2;
						medianPostion++;
					}

					else if (uniqueWordCount < *Median)
					{
						medianValue = ((double)*--Median + (double)tempMedian) / 2;
						medianPostion--;
					}
					else
					{
						medianValue = *Median;

					}
				}
			}
			feature2OutputFile << setprecision(2) << fixed << medianValue << endl;
			singleTweet.clear();
		}
		inputfile.close();
		feature2OutputFile.close();

	}

	else cout << "Unable to open file";
	clock_t stop_m1 = clock();
	cout << "The time it took to build map<int, string> is "
		<< double(stop_m1 - start_m1) / CLOCKS_PER_SEC << " seconds" << '\n';
	for (map<string, long int>::iterator it = tweets.begin(); it != tweets.end(); ++it)
		feature1OutputFile << it->first << "		" << it->second << '\n';
	feature1OutputFile.close();
	cout << "Done" << "\n";
	char ch = 0;
	cin >> ch;

	return 0;


}
