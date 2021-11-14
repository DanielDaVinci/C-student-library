#define elif else if

void swap(int * first_index, int * second_index)
{
    int exp = *first_index;
    *first_index = *second_index;
    *second_index = exp;
}

void quick_sort(int * begin_index, int * end_index)
{
    if (end_index - begin_index <= 0)
        return;

    int * mid = begin_index;
    int * cur = end_index;
    int move = -1;

    while (1)
    {
        if ((*mid > *cur && move == -1) || (*mid < *cur && move == 1))
        {
            swap(mid, cur);
            int d = cur - mid;
            mid = cur;
            cur = mid - d;

            move *= -1;
        }

        cur += move;
        if (cur == mid)
            break;
    }

    quick_sort(begin_index, mid - 1);
    quick_sort(mid + 1, end_index);
}
