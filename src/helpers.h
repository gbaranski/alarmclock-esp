boolean checkArrays(uint8_t arrayA[], uint8_t arrayB[], size_t numItemsArrayA, size_t numItemsArrayB)
{
    boolean same = true;
    size_t numItems = numItemsArrayA > numItemsArrayB ? numItemsArrayA : numItemsArrayB;

    for (int i = 0; i < numItems && same; i++)
    {
        same = arrayA[i] == arrayB[i];
    }
    return same;
}
