#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include "ArrayOper.h"
#include "config.h"
#include "MyUtil.h"
#include <string.h>
#include <assert.h>
#include "Heap.h"
#include <map>

#pragma warning(disable: 4786)

void printSumPairs(int a[], int n, int sum)
{
	int i, j;
	for(i = 0, j = n - 1; i < j;)
	{
		//bigger, go to the smaller j
		if(a[i] + a[j] > sum)
		{
			j--;
		}
		//smaller, go to the bigger i
		else if(a[i] + a[j] < sum)
		{
			i++;
		}
		//find one pair
		else
		{
			printf("(a[%d]=%d,a[%d]=%d) \n", i, a[i], j, a[j]);
			i++;
			j--;
		}
	}
}

void printSumPairsDup(int a[], int n, int sum)
{
	int i, j, k, l;
	for(i = 0, j = n - 1; i < j;)
	{
		//bigger, go to the smaller j
		if(a[i] + a[j] > sum)
		{
			j--;
		}
		//smaller, go to the bigger i
		else if(a[i] + a[j] < sum)
		{
			i++;
		}
		//find one pair
		else
		{
			k = i;
			l = j;
			for(i = k; i < n && a[k] == a[i]; i++)
			{
				for(j = l; j >= 0 && a[l] == a[j]; j--)
				{
					if(i < j)
					{
						printf("(a[%d]=%d,a[%d]=%d) \n", i, a[i], j, a[j]);
					}
				}
			}
		}
	}
}

/************************************************************************/
/* 2. Check an array if a post order of BST                             */
/************************************************************************/

bool checkSeqIfPostOrderOfBST(int a[], int start, int end)
{
	if(start == end)
	{
		return true;
	}

	int i, j;
	for(i = start; i < end; i++)
	{
		if(a[i] > a[end])
		{
			break;
		}
	}
	for(j = i; j < end; j++)
	{
		if(a[j] <= a[end])
		{
			return false;
		}
	}
	if(i > start)
	{
		if(!checkSeqIfPostOrderOfBST(a, start, i - 1))
		{
			return false;
		}
		
	}
	if(end - 1 >= i)
	{
		return checkSeqIfPostOrderOfBST(a, i, end - 1);
	}
	return true;
}
bool checkSeqIfPostOrderOfBST(int a[], int n)
{
	return checkSeqIfPostOrderOfBST(a, 0, n - 1);
}

/************************************************************************/
/* 3. Binary search from an array                                       */
/************************************************************************/
int binarySearch(int a[], int from, int to, int key)
{
	if(from > to)
	{
		return -1;
	}
	while(from <= to)
	{
		int mid = (from + to) >> 1;
		if(key < a[mid])
		{
			to = mid - 1;
		}
		else if(key > a[mid])
		{
			from = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -(from + 1);
}
/************************************************************************/
/* 4. max sum of continuous sub-array                                   */
/************************************************************************/
int maxsumsub(int array[], int n, int* pStart, int* pEnd)
{
	int maxsum = 0, sum = 0;
	int from = 0, end = 0;
	
	int i;
	for(i = 0; i < n; i++)
	{
		sum += array[i];
		
		if(sum > maxsum)
		{
			maxsum = sum;
			end = i;
			if(pEnd != NULL)
			{
				*pStart = from;
				*pEnd = end;
			}
		}
		
		if(sum < 0)
		{
			sum = 0;
			from = i + 1;
		}
	}
	
	return maxsum;
}
int maxsumsub_dp(int a[], int n, int* pStart, int* pEnd)
{
	int maxsum = 0;

	/*
	int* c = new int[n];
	c[0] = a[0];

	for(int i = 1; i < n; i++)
	{
		if(c[i - 1] > 0)
		{
			c[i] = c[i - 1] + a[i];
		}
		else
		{
			c[i] = a[i];
		}

		if(c[i] > maxsum)
		{
			maxsum = c[i];
		}
	}
	delete[] c;
	*/
	
	//Optimized, without extra space
	int sum = -1;
	for(int i = 0; i < n; i++)
	{
		if(sum > 0)
		{
			sum += a[i];
		}
		else
		{
			sum = a[i];
			*pStart = i;
		}

		if(sum > maxsum)
		{
			maxsum = sum;
			*pEnd = i;
		}
	}

	return maxsum;
}

int lowest_bit(int x)
{
	return x & ~(x - 1);
}

void find2distinct(int a[], int n, int* x, int* y)
{
	int i, s = 0;
	for(i = 0; i < n; i++)
	{
		s ^= a[i];
	}

	*x = 0, *y = 0;
	int lowbit = lowest_bit(s);
	for(i = 0; i < n; i++)
	{
		if( (a[i] & lowbit) != 0)
		{
			*x ^= a[i];
		}
		else
		{
			*y ^= a[i];
		}
	}
}

void find3distinct(int a[], int n, int* x, int* y, int* z)
{
	int i, s = 0;
	for(i = 0; i < n; i++)
	{
		s ^= a[i];
	}

	*x = 0, *y = 0, *z = 0;
	int lowbit = lowest_bit(s);
	int flip = 0;

	for(i = 0; i < n; i++)
	{
		flip ^= lowest_bit(s ^ a[i]);
	}

	//flip = lowest_bit(x ^ y) ^ lowest_bit(x ^ z) ^ lowest_bit(y ^ z);
	for(i = 0; i < n; i++)
	{
		if(lowest_bit(s ^ a[i]) == flip)
		{
			*x ^= a[i];
		}
	}

	//swap out the first value
	for(i = 0; i < n; i++)
	{
		if(a[i] == *x)
		{
			int tmp = a[i];
			a[i] = a[n - 1];
			a[n - 1] = tmp;
			break;
		}
	}

	find2distinct(a, n - 1, y, z);
}

void find2miss(int a[], int n, int* x, int* y)
{
	int i, curr_xor = 0, full_xor = 0;
	for(i = 0; i < n - 2; i++)
	{
		curr_xor ^= a[i];
	}
	for(i = 1; i <= n; i++)
	{
		full_xor ^= i;
	}

	//t = x ^ y
	int t = curr_xor ^ full_xor;
	int lowbit_t = lowest_bit(t);
	//split the array into 2 part, 
	//the 1st part elements with same low bit of t, 
	//the 2nd part elements without same low bit of t
	int a1 = 0, a2 = 0;

	//a1 including x
	for(i = 1; i <= n; i++)
	{
		if(i & lowbit_t)
		{
			a1 ^= i;
		}
	}

	//a2 excluding y
	for(i = 0; i < n - 2; i++)
	{
		if((a[i] & lowbit_t) == 0)
		{
			a2 ^= a[i];
		}
	}

	*x = (a1^a2^curr_xor);
	*y = ((*x) ^ t);
}

/*
http://www.felix021.com/blog/read.php?1587
http://www.iteye.com/topic/1054321
http://yzmduncan.iteye.com/blog/1546503
*/
int lis(int a[], int n, int d[], int mem[])
{
	d[0] = a[0];
	mem[0] = 1;

	int i, j, len = 1;
	for(i = 1; i < n; i++)
	{
		if(a[i] > d[len - 1])
		{
			j = len++;
		}
		else
		{
			int lo = 0, hi = len - 1, mid;
			while(lo <= hi)
			{
				mid = (lo + hi) / 2;
				if(a[i] > d[mid])
				{
					lo = mid + 1;
				}
				else
				{
					hi = mid - 1;
				}
			}
			j = lo;
		}
		d[j] = a[i];
		mem[i] = j + 1;
	}
	return len;
}

void reverse(int a[], int low, int high)
{
	int i, j;
	for(i = low, j = high; i < j; i++, j--)
	{
		swap(a[i], a[j]);
	}
}

void rotate1(int a[], int low, int high, int distance)
{
	int n = high - low + 1;
	if(n <= 0)
	{
		return;
	}

	distance %= n;
	if(distance < 0)
	{
		distance += n;
	}
	if(distance == 0)
	{
		return;
	}

	int start, moved, i, displaced;
	for(start = low, moved = 0; moved < n; start++)
	{
		i = start;
		displaced = a[start];

		do 
		{
			//case: low = 7, high = 9, distance = 2
			i += distance;
			if(i > high)
			{
				i -= n;
			}

			//i = low + ((i - low) + distance) % n;
			swap(displaced, a[i]);
			moved++;
		} while (i != start);
	}
}

void rotate2(int a[], int low, int high, int distance)
{
	int n = high - low + 1;
	if(n <= 0)
	{
		return;
	}


	distance %= n;
	if(distance < 0)
	{
		distance += n;
	}
	if(distance == 0)
	{
		return;
	}

	reverse(a, low, high - distance);
	reverse(a, high - distance + 1, high);
	reverse(a, low, high);
}

void merge(int a[], int l, int r, int m)
{
	int i = l, j = m + 1, k;
	while(i <= r && j <= r && i < j)
	{
		while(a[i] <= a[j] && i < j)
		{
			i++;
		}
		k = j;
		while(a[i] > a[j] && j <= r)
		{
			j++;
		}
		rotate1(a, i, j - 1, j - k);
		i += (j - k) + 1;
	}
}

int rand_n(int n)
{
	srand(time(NULL));

	return 1 + rand() % n;
}
int rand_m(int n, int m)
{
	//make sure n < m && n * n >= m
	int t = ((n * n) / m) * m;
	int x;
	do 
	{
		x = n * (rand_n(n) - 1) + rand_n(n);
	} while (x > t);

	return 1 + (x % m);
}

/*
move all the "*" to the left side, and others to the right side,
keep the original order
*/
void reorder(char* str, int n)
{
	/*
	int i , j = n-1;  
    for(i = n - 1 ; i >= 0 ; --i)  
    {
		// j >= i
		//i is the index of non-"*"
        if(str[i] != '*')  
        {  
			//j is the index of "*"
            if(str[j] == '*')  
            {  
                str[j] = str[i];  
                str[i] = '*';  
            }
            --j; 
        }  
    }
	*/
	int i, count = 0;
	for(i = n - 1; i >= 0; i--)
	{
		if(str[i] == '*')
		{
			count++;
		}
		else if(count > 0)
		{
			str[i + count] = str[i];
		}
	}
	for(i = count - 1; i >= 0; i--)
	{
		str[i] = '*';
	}
}

int find_min_in_rotate(int a[], int left, int right)
{
	int m;
	while(left <= right)
	{
		if(a[left] <= a[right])
		{
			return left;
		}
		m = (left + right) / 2;
		if(a[left] <= a[m])
		{
			left = m + 1;
		}
		else
		{
			if(a[m] < a[m-1])
			{
				return m;
			}
			else
			{
				right = m - 1;
			}
		}
	}
	return -1;
}

struct Entry
{
	int val;
	int index;
};

int EntryCompare1(const void* arg1, const void* arg2)
{
	const Entry* e1 = (const Entry*)arg1;
	const Entry* e2 = (const Entry*)arg2;
	
	return e1->val - e2->val;
}

static int makeIndex(int n, int i, int j)
{
	return j * n + i;
}

static void getIndex2(int n, int index, int& i, int& j)
{
	j = index / n;
	i = index % n;
}

static Entry* makeEntry(int a[], int n, int b[], int i, int j)
{
	Entry* pEntry = new Entry();
	pEntry->index = makeIndex(n, i, j);
	pEntry->val = a[i] + b[j];

	return pEntry;
}

static void insertNewEntry(std::map<int, bool>& indexMap, Heap* pHeap, int a[], int n, int b[], int i, int j)
{
	int index = makeIndex(n, i, j);

	if(indexMap.find(index) != indexMap.end())
	{
		return;
	}

	Entry* pEntry = new Entry();
	pEntry->index = index;
	pEntry->val = a[i] + b[j];
	
	pHeap->insert(pEntry);

	indexMap[index] = true;
}


//a, b两个有序数组，分别从a,b数组中取出一个数相加取和，按顺序打印出前k个这样的和
void ksum(int a[], int n, int b[], int m, int k)
{
	std::map<int, bool> indexMap;

	Heap* pHeap = new Heap();
	pHeap->setCompareFunc(EntryCompare1);

	int i = 0, j = 0;
	Entry* pEntry = NULL;

	insertNewEntry(indexMap, pHeap, a, n, b, i, j);

	for(int count = 0; count < k && pHeap->size() > 0; count++)
	{
		pEntry = (Entry*)pHeap->removeTop();
		getIndex2(n, pEntry->index, i, j);

		printf("(a[%d]=%d, b[%d]=%d)=%d\n", i, a[i], j, b[j], pEntry->val);

		if(i + 1 < n)
		{
			insertNewEntry(indexMap, pHeap, a, n, b, i + 1, j);
		}

		if(j + 1 < m)
		{
			insertNewEntry(indexMap, pHeap, a, n, b, i, j + 1);
		}

		delete pEntry;
	}
}

void testArrayOper()
{
#if ((ARRAY_OPER_TEST) == 1)
	//int a[] = {3, 4, -5, 50, -90, 7, 6, -12, 80, -4};
	int a[] = {-3, -4, -5, 50, -90, 7, 6, -12, 80, -40, 41};
	int n = sizeof(a)/sizeof(int);
	//	genseq(a, n);
	//	genrand(a, n);
	//	quickSort(a, n);
	output(a, n);
	
	int i;
	int result = 0;
	//	printSumPairsDup(a, n, n * 3);
	
	//	cout<<binarySearch(a, 0, n - 1, 0.3 * n)<<endl;
	
	int start, end;
	result = maxsumsub(a, n, &start, &end);
	cout<<"maxsumsub: "<<result<<endl;
	for(i = start; i <= end; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	start = end = 0;

	result = maxsumsub_dp(a, n, &start, &end);
	cout<<"maxsumsub_dp: "<<result<<endl;
	for(i = start; i <= end; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	int b[] = {1 ,1 ,1, 1, 1, 1, 1};
	n = sizeof(b)/sizeof(int);
	
	i = binarySearch(b, 0, n - 1, 2);
	cout<<i<<endl;

	int c[] = {1, 10, 20, 9, 20, 8, 9, 1};
	int x = 0, y = 0;
	find2distinct(c, sizeof(c)/sizeof(c[0]), &x, &y);
	printf("The 2 distinct number: x=%d, y=%d\n", x, y);

	int d[] = {1, 10, 20, 9, 20, 8, 9, 1, 23, 23, 4};
	int z = 0;
	find3distinct(d, sizeof(d)/sizeof(d[0]), &x, &y, &z);
	printf("The 3 distinct number: x=%d, y=%d, z=%d\n", x, y, z);


	int e[] = {1, /*2,*/ 3, 4, 5, 6, 7, 8, 9, /*10*/};
	find2miss(e, 10, &x, &y);
	printf("The 2 missing number: x=%d, y=%d\n", x, y);

	int f[] = {/*2,1,5,3,6,4,8,9,7*/1, 1, 1, 4, 5, 6, 7, 8};
	int tmp1[20], tmp2[20];
	n = sizeof(f)/sizeof(f[0]);
	result = lis(f, n, tmp1, tmp2);
	printf("lis length = %d\n", result);
	printf("lis content = ");
	for(i = n - 1; i >= 0 && result > 0; i--)
	{
		if(tmp2[i] == result)
		{
			printf("%d ", f[i]);
			result--;
		}
	}
	printf("\n");

	n = COUNTOF(f);
	int distance = 7;
	rotate1(f, 0, n - 1, distance);
	output(f, COUNTOF(f));
	rotate1(f, 0, n - 1, -distance);
	output(f, COUNTOF(f));

	rotate2(f, 0, n - 1, distance);
	output(f, COUNTOF(f));
// 	rotate2(f, 0, n - 1, -distance);
// 	output(f, COUNTOF(f));

	int minIndex = find_min_in_rotate(f, 0, n - 1);
	printf("min[%d]=%d\n", minIndex, f[minIndex]);

	int aa[] = {1, 2, 3, 6, 9, 10, 4, 5, 7, 8, 11};
	//int aa[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 5, 1};
	//int aa[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int low = 0, high = COUNTOF(aa) - 1, m = high / 2; 
	merge(aa, low, high, m);
	output(aa, COUNTOF(aa));

	char str[] = "1**2**3*4";
	reorder(str, strlen(str));
	printf("%s\n", str);

	
	int arrayA[] = {1, 4, 6, 8, 10};
	n = COUNTOF(arrayA);

	int arrayB[] = {2, 3, 4, 5, 6, 7, 9, 14};
	m = COUNTOF(arrayB);

	ksum(arrayA, n, arrayB, m, n * m / 2);

	printSep(__FILE__);
#endif
}
