#include "shade.h"

std::string encrypt(std::string plain)
{
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

    extern std::string _key_, _iv_;

    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
        key[i] = _key_[i];

    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++)
        iv[i] = _iv_[i];

    std::string cipher;

    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption e;
    e.SetKeyWithIV(key, sizeof(key), iv);
    CryptoPP::StringSource(plain, true,
                           new CryptoPP::StreamTransformationFilter(e,
                                                                    new CryptoPP::StringSink(cipher)));

    return encode(cipher);
}

std::string decrypt(std::string cipher)
{
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

    extern std::string _key_, _iv_;

    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
        key[i] = _key_[i];

    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++)
        iv[i] = _iv_[i];

    std::string recovered;

    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv);
    CryptoPP::StringSource(decode(cipher), true,
                           new CryptoPP::StreamTransformationFilter(d,
                                                                    new CryptoPP::StringSink(recovered)));

    return recovered;
}

std::string encode(std::string orig)
{
    std::string encoded;

    encoded.clear();
    CryptoPP::StringSource(orig, true,
                           new CryptoPP::HexEncoder(
                               new CryptoPP::StringSink(encoded)));

    return encoded;
}

std::string decode(std::string orig)
{
    std::string decoded;

    decoded.clear();
    CryptoPP::StringSource(orig, true,
                           new CryptoPP::HexDecoder(
                               new CryptoPP::StringSink(decoded)));

    return decoded;
}

char someRANDOMnonHexChar()
{
    duthomhas::csprng rng;
    extern std::string delim;
    return delim[rng() % 20];
}
