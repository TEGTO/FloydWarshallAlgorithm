#include "FloydWarshallAlgorithm.h"

using namespace std;
bool checkArraysEqualing(int** arr, int** arr2, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			if (arr2[i][j] != arr[i][j])
				return false;
	}
	return true;
}
void printMatrix(int** arr, int row, int col, int mode)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j%2==0)
				SetConsoleTextAttribute(hConsole, mode==1?12:9);
			else
				SetConsoleTextAttribute(hConsole, 15);
			switch (mode)
			{
			case 1:
				if (arr[i][j] != INT_MIN && arr[i][j] != INT_MAX)
					cout << arr[i][j] << "   ";
				else if (arr[i][j] == INT_MIN)
					cout << "-inf" << " ";
				else if (arr[i][j] == INT_MAX)
					cout << "inf" << " ";
				break;
			case 2:
				if (arr[i][j] == INT_MIN || arr[i][j] == INT_MAX || arr[i][j]==0)
					cout << "nil" << " ";
				else 
					cout << arr[i][j] << "   ";
				break;
			default:
				break;
			}
			
		}
		SetConsoleTextAttribute(hConsole, 15);
		cout << endl;
	}
}
void calculatePMatrix(int** pArr, int row, int col, int k)
{
	int** pArrBuffer = new int* [row];
	for (int i = 0; i < row; i++)
	{
		pArrBuffer[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			pArrBuffer[i][j] = pArr[i][j];
		}
	}
	int buffer;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
				if (k <= -1)
				{
					if (i == j || pArr[i][j] == INT_MAX || pArr[i][j] == INT_MIN)
						pArr[i][j] = INT_MAX;
					else
						pArr[i][j] = i + 1;
				}
				else
				{
					if (pArrBuffer[i][k] == INT_MAX || pArrBuffer[k][j] == INT_MAX)
						buffer = INT_MAX;
					else if (pArrBuffer[i][k] == INT_MIN || pArrBuffer[k][j] == INT_MIN)
						buffer = INT_MIN;
					else
						buffer = pArrBuffer[i][k] + pArrBuffer[k][j];
					if (i != j && (pArrBuffer[i][j] > buffer))
						pArr[i][j] = pArrBuffer[k][j];
				}
		
		}
	}
	printMatrix(pArr, row, col, 2);

}
void floydWarshallAlgorithm(int ** arr,int row, int col)
{
	system("CLS");
	int** arr2 = new int* [row];
	int** pArr = new int* [row];
	for (int i = 0; i < row; i++)
	{
		arr2[i] = new int[col];
		pArr[i] = new int[col];
		for (int j = 0; j < col; j++)
			pArr[i][j] = arr[i][j];
	}

	int k = -1, buffer;
	while (!checkArraysEqualing(arr,arr2,row,col))
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				arr2[i][j] = arr[i][j];
		cout << "\n\nD^("<< k+1<<") : " << endl;
		printMatrix(arr2, row, col,1);
		cout << "\n\nP^(" << k + 1 << ") : " << endl;
		calculatePMatrix(pArr, row, col,k);
		k++;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (arr2[i][k]==INT_MAX || arr2[k][j]==INT_MAX)
				buffer = INT_MAX;
				else if (arr2[i][k] == INT_MIN || arr2[k][j] == INT_MIN)
				buffer = INT_MIN;
				else
				buffer= arr2[i][k] + arr2[k][j];
				if (i !=j && (arr2[i][j]> buffer))
					arr[i][j] = buffer;
			}
		}
	}

}

int main()
{
	cout << "made by TE (aka Evgenii)\nFloyd-Warshall Algorithm\n\n";
	int row, col;
	cout << "Enter Rows: ";
	cin >> row;
	cout << "Enter Columns: ";
	cin >> col;
	int** arr = new int* [row];
	for (int i = 0; i < row; i++)
		arr[i] = new int[col];
	cout << "\nEnter D^(0) matrix" << endl;
	cout << "*type 'inf (-inf)' for infinite (-infinite)\n" << endl;
	string c;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "Enter"<<"("<<i+1<<","<<" "<<j+1<<")"<<" element: ";
			cin >> c;
			if (c != "inf")
				arr[i][j] = stoi(c);
			else if (c == "inf")
				arr[i][j] = INT_MAX;
			else if (c == "-inf")
				arr[i][j] = INT_MIN;
		}
	}

	floydWarshallAlgorithm(arr,row, col);
	system("pause");
	return 0;
}