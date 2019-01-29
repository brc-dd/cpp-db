string encrypt(string str)
{
    for(int i=0; i<iterateOver; i++)
        str=base64_encode(reinterpret_cast<const unsigned char*>(str.c_str()),str.length());
    return str;
}

string decrypt(string str)
{
    for(int i=0; i<iterateOver; i++)
        str=base64_decode(str);
    return str;
}