#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "decipher.h" 
 
size_t bit_get(const unsigned char* data, size_t idx)
{
     
    size_t i = idx/8;
    idx= idx % 8;
     
    size_t sht= 0x80;
    sht >>= idx;
 
    if( data[i] & sht)
        return 1;
    else
        return 0;
}
 
unsigned char bit_get_sequence(const unsigned char* data, size_t idx, size_t how_many)
{
 
    unsigned char ret1 = 0x00;
    size_t count = 0;
 
    for(size_t i =idx ; count < how_many ; i++)
    {
 
        ret1 |= bit_get(data, i);
        if(count < how_many - 1)
            ret1 <<= 1;
 
        count++;
    }
 
    return ret1;
}
 
unsigned char* decipherString(unsigned char* str, unsigned char* key, size_t size)
{
    unsigned char dec_key[9];
    unsigned char new_key[9];
    unsigned char tmp;
    unsigned char* deciph = calloc(1, (size+1) * sizeof(char));
     
    size_t k = 0;
 
 
    for(size_t i=0 ; i<8 ; i++)
        {
            dec_key[i] = bit_get_sequence(key, (i+(2*i)), 3);  //001 111 000 101 011 110 100 010
        }
    dec_key[8] = '\0';
     
    for(size_t j=0 ; j< size ; j++)
    {    
 
        if ((j % 8 == 0) && (j != 0))
        {
            new_key[8] = '\0';
         
            for(size_t i=0 ; i<8 ; i++)
            {
                dec_key[7-i] = new_key[i];
                 
            }
            dec_key[8] = '\0';
 
            k=0;
        }
 
        for(size_t i=0 ; i<7; i++)
        {
            tmp = str[j];
            deciph[j] |= ((tmp >> dec_key[i]) & 0x01);
            deciph[j] <<= 1;
        }
        deciph[j] |= ((tmp >> dec_key[7]) & 0x01);
 
        new_key[k] = 0;
        new_key[k] |= (deciph[j] & 0xe0) >> 5;
         
        k++;
         
    }
    deciph[size] = '\0';
 
    for(size_t j=0 ; j< size ; j++)
    {
        deciph[j] &= 0x1f;
 
    }
 
 
 
    return deciph;
}
