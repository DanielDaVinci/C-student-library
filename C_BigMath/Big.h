#define elif else if

typedef struct big
{
    int m_int[100];
    int m_float[100];
    int size_int;
    int size_float;
    int mark;
} big;

big reset() // Конструктор
{
    big a;
    for (int i = 0; i < 100; i++)
    {
        a.m_int[i] = 0;
        a.m_float[i] = 0;
    }
    a.size_int = 0;
    a.size_float = 0;
    a.mark = 1;
    return a;
}


/****************

  Преобразования

***************/

big convert_int_to_big(int value) // из int
{
    big a = reset();
    int size = 0;
    int ch = value;
    while (ch != 0)
    {
        size++;
        ch /= 10;
    }
    a.size_int = size;
    for (int i = a.size_int-1; i >= 0; i--, value /= 10)
        a.m_int[i] = value % 10;

    return a;
}

/****************

  Ввод и Вывод

***************/

void input_big(big *value) // Ввод
{
    *value = reset();

    char input_value;
    int Ok = 1;
    int dot;

    while (Ok)
    {
        Ok = 0;
        value->mark = 1;
        value->size_int = 0;
        value->size_float = 0;

        input_value = getchar();
        if (input_value == '-')
        {
            value->mark = -1;
            input_value = getchar();
        }
        if (input_value == '\n')
            Ok = 1;
        else
            for (dot = 0; input_value != '\n'; input_value = getchar())
            {
                if (input_value >= '0' && input_value <= '9')
                {
                    if (!dot)
                    {
                        value->m_int[value->size_int++] = (int)input_value-48;
                    }
                    else
                    {
                        value->m_float[value->size_float++] = (int)input_value-48;
                    }
                }
                elif (( input_value == '.' ||  input_value == ',') && dot == 0)
                    dot = 1;
                else
                    Ok = 1;
            }
        if (Ok)
            printf("INCORRECT VALUE\nValue must have only numbers\nInput new value:");
    }
}

void print_big(big value) // Вывод
{
    if (value.mark == -1)
        printf("-");
    if (value.size_int == 0)
        printf("%d", 0);
    for (int i = 0 ; i < value.size_int; i++)
    {
        printf("%d", value.m_int[i]);
    }
    if (value.size_float != 0)
        printf(".");
    for (int i = 0 ; i < value.size_float; i++)
    {
        printf("%d", value.m_float[i]);
    }
    printf("\n");
}

/****************

    Операции

***************/

int compare(big a, big b) // Сравнение 1 - a > b, -1 - a < b, 0 - a = b
{
    if (a.size_int > b.size_int)
        return 1;
    elif (a.size_int < b.size_int)
        return -1;
    else
    {
        for (int i = 0; i < a.size_int; i++)
            if (a.m_int[i] > b.m_int[i])
                return 1;
            elif (a.m_int[i] < b.m_int[i])
                return -1;
        for (int i = 0; i < max(a.size_float, b.size_float); i++)
            if (a.m_float[i] > b.m_float[i])
                return 1;
            elif (a.m_float[i] < b.m_float[i])
                return -1;
        return 0;
    }
}

big minus(big a, big b) // Разность
{
    big result = reset();

    int com = compare(a, b); // меняем местами, чтобы было легче вычитать
    if (com == -1)
    {
        big c = a;
        a = b;
        b = c;
        result.mark = -1;
    }
    elif (com == 0)
    {
        result.m_int[0] = 0;
        result.size_int = 1;
        return result;
    }

    int dif;
    a.size_float = max(a.size_float, b.size_float);
    for (int i = max(a.size_float, b.size_float)-1; i >= 0; i--) // вычитаем целую часть
    {
        dif = a.m_float[i] - b.m_float[i];
        if (dif >= 0)
            a.m_float[i] = dif;
        elif (i == 0)
        {
            a.m_float[i] = 10 + dif;
            b.m_int[b.size_int-1] += 1;
        }
        else
        {
            a.m_float[i] = 10 + dif;
            b.m_float[i-1] += 1;
        }
    }
    for (int i = b.size_int-1 ; i >= 0; i--) // вычитаем дробную часть
    {
        dif = a.m_int[i + (a.size_int - b.size_int)] - b.m_int[i];
        if (dif >= 0)
            a.m_int[i + (a.size_int - b.size_int)] = dif;
        elif (i == 0)
        {
            a.m_int[i + (a.size_int - b.size_int)] = -dif;
        }
        else
        {
            a.m_int[i + (a.size_int - b.size_int)] = 10 + dif;
            b.m_int[i-1] += 1;
        }
    }

    for (int i = 0; i < a.size_int; i++)
    {
        if ((a.m_int[i] != 0) || (i == a.size_int-1))
            for (; i < a.size_int; i++)
                result.m_int[result.size_int++] = a.m_int[i];
    }
    for (int i = a.size_float-1; i >= 0; i--)
    {
        if (a.m_float[i] != 0)
            for (; i >= 0; i--, result.size_float++)
                result.m_float[i] = a.m_float[i];
    }
    return result;
}

big division(int value, long long b) // Деление
{
    big result = reset();
    big a = convert_int_to_big(value);

    long long ch = a.m_int[0];
    int j = 0;
    while (j < a.size_int) // целая часть
    {
        while ((ch / b == 0) && (j < a.size_int))
            ch = ch * 10 + a.m_int[++j];

        if (j < a.size_int)
        {
            result.m_int[result.size_int++] = ch / b;
            ch %= b;
        }
    }
    while ((ch != 0) && (result.size_float < sizeof(result.m_float) / sizeof(result.m_float[0]))) // дробная
    {
        while (ch / b == 0)
            ch *= 10;

        result.m_float[result.size_float++] = ch / b;
        ch %= b;
    }
    return result;
}

big babs(big a) // Модуль
{
    a.mark = 1;
    return a;
}


