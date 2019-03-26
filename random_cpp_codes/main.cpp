#include<iostream>
#include<algorithm>
using namespace std;
/*int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
void countSort(int arr[], int n, int exp,int ns[])
{
    int output[n]={0};
    int output1[n]={0};
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
    	if(count[(arr[i]/exp)%10]>0)
    	{
        	output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        	output1[count[ (arr[i]/exp)%10 ] - 1] = ns[i];
        	count[ (arr[i]/exp)%10 ]--;
    	}
    }
    for (i = 0; i < n; i++)
        {
        	arr[i] = output[i];
        	ns[i] = output1[i];
		}
}
void radixsort(int arr[], int n,int ns[])
{
    int m = getMax(arr, n);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp,ns);
}*/

void swap(int *x,int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
}

int partition(int arr[],int low,int high,int n[])
{
	int i=low-1;
	int temp=arr[high];
	for(int j=low;j<high;j++)
	{
		if(arr[j]<=temp)
		{
			++i;
			swap(&arr[i],&arr[j]);
			swap(&n[i],&n[j]);
		}
	}
	swap(&arr[i+1],&arr[high]);
	swap(&n[i+1],&n[high]);
	return i+1;
}

void quicksort(int arr[],int low,int high,int n[])
{
	if(low<high)
	{
		int p=partition(arr,low,high,n);
		quicksort(arr,low,p-1,n);
		quicksort(arr,p+1,high,n);
	}
}

int main()
{
	int p,s;
	cin>>p>>s;
	int n[s],sub[s],res[p];
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<s;j++)
		{cin>>sub[i];}
		for(int j=0;j<s;j++)
		cin>>n[i];

		quicksort(sub,0,s-1,n);
		
		res[i]=0;
		for(int j=0;j<s-1;j++)
		{
			if(n[j]>n[j+1]) res[i]++;
		}
	}
	int final[p];
	for(int i=0;i<p;i++)
	final[i]=i+1;
	quicksort(res,0,p-1,final);
	for(int i=0;i<p;i++)
		cout<<final[i]<<endl;
	return 0;
}
