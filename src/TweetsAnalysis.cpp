#include "header.h"

/*  This function is used to calculate streaming median
by comparing new input with existing Median and
adjusting median postion and pointer to median
*/
double CalculateStreamingMedian(int listsize, int uniqueWordCount, multiset<int>::iterator& Median, int& medianPostion)
{
	int tempMedian;
	double medianValue;

	if (uniqueWordCount < *Median)
		medianPostion++;

	if (listsize % 2 == 1)
	{
		if ((listsize / 2 + 1) < medianPostion)
		{
			medianPostion--;
			Median--;
		}
		else if ((listsize / 2 + 1) > medianPostion)
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
	return medianValue;
}

int main(int argc)
{
	map<string, long int> tweets;
	map<string, long int> singleTweet;
	multiset <int> uniqueWordsList;
	multiset<int>::iterator Median;
	double medianValue;
	string line, word;
	int uniqueWordCount = 0, medianPostion = 0;
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

			uniqueWordsList.insert(uniqueWordCount);

			//The 1st line so median is 1st element
			if (uniqueWordsList.size() == 1)
			{
				Median = uniqueWordsList.begin();
				medianValue = *Median;
				medianPostion++;
			}
			// for any other line function CalculateStreamingMedian is called
			else
			{
				medianValue = CalculateStreamingMedian(uniqueWordsList.size(), uniqueWordCount, Median, medianPostion);
			}
			feature2OutputFile << setprecision(1) << fixed << medianValue << endl;
			singleTweet.clear();
		}
		inputfile.close();
		feature2OutputFile.close();

	}
	else
		printf("Unable to open file");
	for (map<string, long int>::iterator it = tweets.begin(); it != tweets.end(); ++it)
		feature1OutputFile << it->first << "		" << it->second << '\n';
	feature1OutputFile.close();
	printf("Done \n");
	getchar();
	return 0;


}
