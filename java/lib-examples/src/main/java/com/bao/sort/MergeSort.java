package com.bao.sort;

public class MergeSort implements SortUtil.Sort
{

	/* (non-Javadoc)
	 * @see org.rut.util.algorithm.SortUtil.Sort#sort(int[])
	 */
	public void sort(int[] data)
	{
		int[] temp = new int[data.length];
		mergeSort(data, temp, 0, data.length - 1);
	}

	private void mergeSort(int[] data, int[] temp, int l, int r)
	{
		int mid = (l + r) / 2;
		if (l == r)
			return;
		mergeSort(data, temp, l, mid);
		mergeSort(data, temp, mid + 1, r);
		for (int i = l; i <= r; i++)
		{
			temp[i] = data[i];
		}
		int i1 = l;
		int i2 = mid + 1;
		for (int cur = l; cur <= r; cur++)
		{
			if (i1 == mid + 1)
				data[cur] = temp[i2++];
			else if (i2 > r)
				data[cur] = temp[i1++];
			else if (temp[i1] < temp[i2])
				data[cur] = temp[i1++];
			else
				data[cur] = temp[i2++];
		}
	}

}
