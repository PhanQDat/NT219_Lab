#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;
#include <set>
#include "assert.h"

#include <getopt.h> /* for getopt */

#include <cstdlib>
using std::exit;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include <cryptopp/files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/filters.h"
using CryptoPP::ArraySink;
using CryptoPP::ArraySource;
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::Redirector;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/des.h"
using CryptoPP::DES;

#include "cryptopp/ccm.h"
using CryptoPP::CBC_Mode;
using CryptoPP::CFB_Mode;
using CryptoPP::CTR_Mode;
using CryptoPP::ECB_Mode;
using CryptoPP::OFB_Mode;
#include "cryptopp/xts.h"
using CryptoPP::XTS;
#include "cryptopp/ccm.h"
using CryptoPP::CCM;
#include "cryptopp/gcm.h"
using CryptoPP::GCM;
#include <chrono>

#define round_trip_times 1.0
#define round_trip 1

class Operation
{
protected:
    string plain;
    string cipher;
    string decoded;
    char *key_file;
    char *iv_file;
    char *plain_file;
    char *cipher_file;
    CryptoPP::byte key[8];
    CryptoPP::byte iv[DES::BLOCKSIZE];

public:
    Operation(char *&key_file, char *&iv_file, char *&plain_file, char *&cipher_file) : key_file(key_file), iv_file(iv_file), plain_file(plain_file), cipher_file(cipher_file) {}
    virtual ~Operation() {}
    virtual void generate_key_iv(char *key_file, char *iv_file) = 0;
    virtual void encrypt() = 0;
    virtual void decrypt() = 0;
};

class ECB : public Operation
{
public:
    ECB(char *key_file, char *iv_file, char *plain_file, char *cipher_file)
        : Operation(key_file, iv_file, plain_file, cipher_file) {}
    ~ECB() {}
    void generate_key_iv(char *key_file, char *iv_file) override
    {
        AutoSeededRandomPool prng;
        cout << "\nDo you want to generate a new key or enter a key? [1|2]:\n"
             << "1. Generate a new random key\n"
             << "2. Enter a key\n"
             << "Please enter your number: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(key, sizeof(key));

            // Pretty print key
            string encoded;
            StringSource(key, sizeof(key), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "key: " << encoded << endl;

            // Save key to file
            StringSource(key, sizeof(key), true,
                         new FileSink(key_file));
            cout << "key was saved to " << key_file << endl;
        }
        else if (choice == 2)
        {
            try
            {
                cout << "Enter key (Hex format): ";
                cin >> key;
                // Save key to file
                StringSource(key, sizeof(key), true,
                             new HexEncoder(
                                 new FileSink(key_file)));
                cout << "key was saved to " << key_file << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            cerr << "Invalid choice. Exiting program." << endl;
            exit(1);
        }
    }

    void encrypt() override
    {
        if (plain_file != nullptr)
        {
            try
            {
                cout << "reading plain text from " << plain_file << "..." << endl;
                plain.clear();
                FileSource(plain_file, true,
                           new StringSink(plain), false);
                cout << "plain text: " << plain << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Enter plain text: ";
            cin.ignore();
            plain.clear();
            getline(cin, plain);
        }

        ECB_Mode<DES>::Encryption e;
        try
        {
            cout << "reading key from " << key_file << "..." << endl;
            FileSource(key_file, true,
                       new ArraySink(key, sizeof(key)));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }

        e.SetKey(key, sizeof(key));
        decoded.clear();
        // time start
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < round_trip; i++)
        {
            cipher.clear();
            StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        }
        StringSource(cipher, true, new HexEncoder(new StringSink(decoded)));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double averageTime = static_cast<double>(duration) / round_trip_times;
        cout << "cipher: " << decoded << endl;
        cout << "Total times for encryption: " << averageTime << " ms" << std::endl;
        StringSource(decoded, true, new FileSink((char *)"cipher.txt"));
    }

    void decrypt() override
    {
        if (cipher_file != nullptr)
        {
            try
            {
                cout << "reading cipher text from " << cipher_file << "..." << endl;
                cipher.clear();
                FileSource(cipher_file, true,
                           new StringSink(cipher), false);
                cout << "cipher text: " << cipher << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            char choice;
            cout << "Enter cipher text Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter cipher text (Hex format): ";
                cin >> cipher;
            }
            else
            {
                cipher = decoded;
            }
        }

        ECB_Mode<DES>::Decryption d;
        cout << "reading key from " << key_file << "..." << endl;
        FileSource(key_file, true,
                   new ArraySink(key, sizeof(key)));

        d.SetKey(key, sizeof(key));

        string recovered;
        try
        {
            decoded.clear();
            // time start
            auto start = std::chrono::high_resolution_clock::now();
            StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
            for (int i = 0; i < round_trip; i++)
            {
                recovered.clear();
                StringSource s(decoded, true, new StreamTransformationFilter(d, new StringSink(recovered)));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            double averageTime = static_cast<double>(duration) / round_trip_times;
            cout << "recovered text: " << recovered << endl;
            cout << "Total times for decryptionn: " << averageTime << " ms" << std::endl;
            StringSource(decoded, true, new FileSink((char *)"recovered.txt"));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }
    }
};

class CBC : public Operation
{
public:
    CBC(char *key_file, char *iv_file, char *plain_file, char *cipher_file)
        : Operation(key_file, iv_file, plain_file, cipher_file) {}
    ~CBC() {}
    void generate_key_iv(char *key_file, char *iv_file) override
    {
        AutoSeededRandomPool prng;
        cout << "\nDo you want to generate a new key or enter a key? [1|2]:\n"
             << "1. Generate a new random key\n"
             << "2. Enter a key\n"
             << "Please enter your number: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(key, sizeof(key));

            // Pretty print key
            string encoded;
            StringSource(key, sizeof(key), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "key: " << encoded << endl;

            // Save key to file
            StringSource(key, sizeof(key), true,
                         new FileSink(key_file));
            cout << "key was saved to " << key_file << endl;

            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(iv, sizeof(iv));

            // Pretty print iv
            encoded.clear();
            StringSource(iv, sizeof(iv), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "iv: " << encoded << endl;

            // Save iv to file
            StringSource(iv, sizeof(iv), true,
                         new FileSink(iv_file));
            cout << "iv was saved to " << iv_file << endl;
        }
        else if (choice == 2)
        {
            try
            {
                cout << "Enter key (Hex format): ";
                cin >> key;
                // Save key to file
                StringSource(key, sizeof(key), true,
                             new HexEncoder(
                                 new FileSink(key_file)));
                cout << "key was saved to " << key_file << endl;

                cout << "Enter iv (Hex format): ";
                cin >> iv;
                // Save iv to file
                StringSource(iv, sizeof(iv), true,
                             new HexEncoder(
                                 new FileSink(iv_file)));
                cout << "iv was saved to " << iv_file << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            cerr << "Invalid choice. Exiting program." << endl;
            exit(1);
        }
    }

    void encrypt() override
    {
        if (plain_file != nullptr)
        {
            try
            {
                cout << "reading plain text from " << plain_file << "..." << endl;
                plain.clear();
                FileSource(plain_file, true,
                           new StringSink(plain), false);
                cout << "plain text: " << plain << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Enter plain text: ";
            cin.ignore();
            plain.clear();
            getline(cin, plain);
        }

        CBC_Mode<DES>::Encryption e;
        try
        {
            cout << "reading key from " << key_file << "..." << endl;
            FileSource(key_file, true,
                       new ArraySink(key, sizeof(key)));

            cout << "reading iv from " << iv_file << "..." << endl;
            FileSource(iv_file, true,
                       new ArraySink(iv, sizeof(iv)));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }

        e.SetKeyWithIV(key, sizeof(key), iv);

        decoded.clear();
        // time start
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < round_trip; i++)
        {
            cipher.clear();
            StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        }
        StringSource(cipher, true, new HexEncoder(new StringSink(decoded)));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double averageTime = static_cast<double>(duration) / round_trip_times;
        cout << "cipher: " << decoded << endl;
        cout << "Total times for encryption: " << averageTime << " ms" << std::endl;
        StringSource(decoded, true, new FileSink((char *)"cipher.txt"));
    }

    void decrypt() override
    {
        if (cipher_file != nullptr)
        {
            try
            {
                cout << "reading cipher text from " << cipher_file << "..." << endl;
                cipher.clear();
                FileSource(cipher_file, true,
                           new StringSink(cipher), false);
                cout << "cipher text: " << cipher << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            char choice;
            cout << "Enter cipher text Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter cipher text (Hex format): ";
                cin >> cipher;
            }
            else
            {
                cipher = decoded;
            }
        }

        cout << "reading key from " << key_file << "..." << endl;
        FileSource(key_file, true,
                   new ArraySink(key, sizeof(key)));

        cout << "reading iv from " << iv_file << "..." << endl;
        FileSource(iv_file, true,
                   new ArraySink(iv, sizeof(iv)));

        string recovered;
        CBC_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);
        try
        {
            decoded.clear();
            // time start
            auto start = std::chrono::high_resolution_clock::now();
            StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
            for (int i = 0; i < round_trip; i++)
            {
                recovered.clear();
                StringSource s(decoded, true, new StreamTransformationFilter(d, new StringSink(recovered)));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            double averageTime = static_cast<double>(duration) / round_trip_times;
            cout << "recovered text: " << recovered << endl;
            cout << "Total times for decryptionn: " << averageTime << " ms" << std::endl;
            StringSource(decoded, true, new FileSink((char *)"recovered.txt"));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }
    }
};

class OFB : public Operation
{
public:
    OFB(char *key_file, char *iv_file, char *plain_file, char *cipher_file)
        : Operation(key_file, iv_file, plain_file, cipher_file) {}
    ~OFB() {}
    void generate_key_iv(char *key_file, char *iv_file) override
    {
        AutoSeededRandomPool prng;
        cout << "\nDo you want to generate a new key or enter a key? [1|2]:\n"
             << "1. Generate a new random key\n"
             << "2. Enter a key\n"
             << "Please enter your number: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(key, sizeof(key));

            // Pretty print key
            string encoded;
            StringSource(key, sizeof(key), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "key: " << encoded << endl;

            // Save key to file
            StringSource(key, sizeof(key), true,
                         new FileSink(key_file));
            cout << "key was saved to " << key_file << endl;

            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(iv, sizeof(iv));

            // Pretty print iv
            encoded.clear();
            StringSource(iv, sizeof(iv), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "iv: " << encoded << endl;

            // Save iv to file
            StringSource(iv, sizeof(iv), true,
                         new FileSink(iv_file));
            cout << "iv was saved to " << iv_file << endl;
        }
        else if (choice == 2)
        {
            try
            {
                cout << "Enter key (Hex format): ";
                cin >> key;
                // Save key to file
                StringSource(key, sizeof(key), true,
                             new HexEncoder(
                                 new FileSink(key_file)));
                cout << "key was saved to " << key_file << endl;

                cout << "Enter iv (Hex format): ";
                cin >> iv;
                // Save iv to file
                StringSource(iv, sizeof(iv), true,
                             new HexEncoder(
                                 new FileSink(iv_file)));
                cout << "iv was saved to " << iv_file << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            cerr << "Invalid choice. Exiting program." << endl;
            exit(1);
        }
    }

    void encrypt() override
    {
        if (plain_file != nullptr)
        {
            try
            {
                cout << "reading plain text from " << plain_file << "..." << endl;
                plain.clear();
                FileSource(plain_file, true,
                           new StringSink(plain), false);
                cout << "plain text: " << plain << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Enter plain text: ";
            cin.ignore();
            plain.clear();
            getline(cin, plain);
        }

        OFB_Mode<DES>::Encryption e;
        try
        {
            cout << "reading key from " << key_file << "..." << endl;
            FileSource(key_file, true,
                       new ArraySink(key, sizeof(key)));

            cout << "reading iv from " << iv_file << "..." << endl;
            FileSource(iv_file, true,
                       new ArraySink(iv, sizeof(iv)));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }

        e.SetKeyWithIV(key, sizeof(key), iv);

        decoded.clear();
        // time start
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < round_trip; i++)
        {
            cipher.clear();
            StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        }
        StringSource(cipher, true, new HexEncoder(new StringSink(decoded)));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double averageTime = static_cast<double>(duration) / round_trip_times;
        cout << "cipher: " << decoded << endl;
        cout << "Total times for encryption: " << averageTime << " ms" << std::endl;
        StringSource(decoded, true, new FileSink((char *)"cipher.txt"));
    }

    void decrypt() override
    {
        if (cipher_file != nullptr)
        {
            try
            {
                cout << "reading cipher text from " << cipher_file << "..." << endl;
                cipher.clear();
                FileSource(cipher_file, true,
                           new StringSink(cipher), false);
                cout << "cipher text: " << cipher << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            char choice;
            cout << "Enter cipher text Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter cipher text (Hex format): ";
                cin >> cipher;
            }
            else
            {
                cipher = decoded;
            }
        }

        cout << "reading key from " << key_file << "..." << endl;
        FileSource(key_file, true,
                   new ArraySink(key, sizeof(key)));

        cout << "reading iv from " << iv_file << "..." << endl;
        FileSource(iv_file, true,
                   new ArraySink(iv, sizeof(iv)));

        string recovered;
        OFB_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);
        try
        {
            decoded.clear();
            // time start
            auto start = std::chrono::high_resolution_clock::now();
            StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
            for (int i = 0; i < round_trip; i++)
            {
                recovered.clear();
                StringSource s(decoded, true, new StreamTransformationFilter(d, new StringSink(recovered)));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            double averageTime = static_cast<double>(duration) / round_trip_times;
            cout << "recovered text: " << recovered << endl;
            cout << "Total times for decryptionn: " << averageTime << " ms" << std::endl;
            StringSource(decoded, true, new FileSink((char *)"recovered.txt"));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }
    }
};

class CFB : public Operation
{
public:
    CFB(char *key_file, char *iv_file, char *plain_file, char *cipher_file)
        : Operation(key_file, iv_file, plain_file, cipher_file) {}
    ~CFB() {}
    void generate_key_iv(char *key_file, char *iv_file) override
    {
        AutoSeededRandomPool prng;
        cout << "\nDo you want to generate a new key or enter a key? [1|2]:\n"
             << "1. Generate a new random key\n"
             << "2. Enter a key\n"
             << "Please enter your number: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(key, sizeof(key));

            // Pretty print key
            string encoded;
            StringSource(key, sizeof(key), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "key: " << encoded << endl;

            // Save key to file
            StringSource(key, sizeof(key), true,
                         new FileSink(key_file));
            cout << "key was saved to " << key_file << endl;

            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(iv, sizeof(iv));

            // Pretty print iv
            encoded.clear();
            StringSource(iv, sizeof(iv), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "iv: " << encoded << endl;

            // Save iv to file
            StringSource(iv, sizeof(iv), true,
                         new FileSink(iv_file));
            cout << "iv was saved to " << iv_file << endl;
        }
        else if (choice == 2)
        {
            try
            {
                cout << "Enter key (Hex format): ";
                cin >> key;
                // Save key to file
                StringSource(key, sizeof(key), true,
                             new HexEncoder(
                                 new FileSink(key_file)));
                cout << "key was saved to " << key_file << endl;

                cout << "Enter iv (Hex format): ";
                cin >> iv;
                // Save iv to file
                StringSource(iv, sizeof(iv), true,
                             new HexEncoder(
                                 new FileSink(iv_file)));
                cout << "iv was saved to " << iv_file << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            cerr << "Invalid choice. Exiting program." << endl;
            exit(1);
        }
    }

    void encrypt() override
    {
        if (plain_file != nullptr)
        {
            try
            {
                cout << "reading plain text from " << plain_file << "..." << endl;
                plain.clear();
                FileSource(plain_file, true,
                           new StringSink(plain), false);
                cout << "plain text: " << plain << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Enter plain text: ";
            cin.ignore();
            plain.clear();
            getline(cin, plain);
        }

        CFB_Mode<DES>::Encryption e;
        try
        {
            cout << "reading key from " << key_file << "..." << endl;
            FileSource(key_file, true,
                       new ArraySink(key, sizeof(key)));

            cout << "reading iv from " << iv_file << "..." << endl;
            FileSource(iv_file, true,
                       new ArraySink(iv, sizeof(iv)));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }

        decoded.clear();
        // time start
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < round_trip; i++)
        {
            e.SetKeyWithIV(key, sizeof(key), iv);
            cipher.clear();
            StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        }
        StringSource(cipher, true, new HexEncoder(new StringSink(decoded)));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double averageTime = static_cast<double>(duration) / round_trip_times;
        cout << "cipher: " << decoded << endl;
        cout << "Total times for encryption: " << averageTime << " ms" << std::endl;
        StringSource(decoded, true, new FileSink((char *)"cipher.txt"));
    }

    void decrypt() override
    {
        if (cipher_file != nullptr)
        {
            try
            {
                cout << "reading cipher text from " << cipher_file << "..." << endl;
                cipher.clear();
                FileSource(cipher_file, true,
                           new StringSink(cipher), false);
                cout << "cipher text: " << cipher << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            char choice;
            cout << "Enter cipher text Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter cipher text (Hex format): ";
                cin >> cipher;
            }
            else
            {
                cipher = decoded;
            }
        }

        cout << "reading key from " << key_file << "..." << endl;
        FileSource(key_file, true,
                   new ArraySink(key, sizeof(key)));

        cout << "reading iv from " << iv_file << "..." << endl;
        FileSource(iv_file, true,
                   new ArraySink(iv, sizeof(iv)));

        string recovered;
        CFB_Mode<DES>::Decryption d;
        try
        {
            decoded.clear();
            // time start
            auto start = std::chrono::high_resolution_clock::now();
            StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
            for (int i = 0; i < round_trip; i++)
            {
                d.SetKeyWithIV(key, sizeof(key), iv);
                recovered.clear();
                StringSource s(decoded, true, new StreamTransformationFilter(d, new StringSink(recovered)));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            double averageTime = static_cast<double>(duration) / round_trip_times;
            cout << "recovered text: " << recovered << endl;
            cout << "Total times for decryptionn: " << averageTime << " ms" << std::endl;
            StringSource(decoded, true, new FileSink((char *)"recovered.txt"));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }
    }
};

class CTR : public Operation
{
public:
    CTR(char *key_file, char *iv_file, char *plain_file, char *cipher_file)
        : Operation(key_file, iv_file, plain_file, cipher_file) {}
    ~CTR() {}
    void generate_key_iv(char *key_file, char *iv_file) override
    {
        AutoSeededRandomPool prng;
        cout << "\nDo you want to generate a new key or enter a key? [1|2]:\n"
             << "1. Generate a new random key\n"
             << "2. Enter a key\n"
             << "Please enter your number: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(key, sizeof(key));

            // Pretty print key
            string encoded;
            StringSource(key, sizeof(key), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "key: " << encoded << endl;

            // Save key to file
            StringSource(key, sizeof(key), true,
                         new FileSink(key_file));
            cout << "key was saved to " << key_file << endl;

            /*---------------------------------*/
            /*------Generate a random key------*/
            /*---------------------------------*/
            prng.GenerateBlock(iv, sizeof(iv));

            // Pretty print iv
            encoded.clear();
            StringSource(iv, sizeof(iv), true,
                         new HexEncoder(
                             new StringSink(encoded)));
            cout << "iv: " << encoded << endl;

            // Save iv to file
            StringSource(iv, sizeof(iv), true,
                         new FileSink(iv_file));
            cout << "iv was saved to " << iv_file << endl;
        }
        else if (choice == 2)
        {
            try
            {
                cout << "Enter key (Hex format): ";
                cin >> key;
                // Save key to file
                StringSource(key, sizeof(key), true,
                             new HexEncoder(
                                 new FileSink(key_file)));
                cout << "key was saved to " << key_file << endl;

                cout << "Enter iv (Hex format): ";
                cin >> iv;
                // Save iv to file
                StringSource(iv, sizeof(iv), true,
                             new HexEncoder(
                                 new FileSink(iv_file)));
                cout << "iv was saved to " << iv_file << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            cerr << "Invalid choice. Exiting program." << endl;
            exit(1);
        }
    }

    void encrypt() override
    {
        if (plain_file != nullptr)
        {
            try
            {
                cout << "reading plain text from " << plain_file << "..." << endl;
                plain.clear();
                FileSource(plain_file, true,
                           new StringSink(plain), false);
                cout << "plain text: " << plain << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Enter plain text: ";
            cin.ignore();
            plain.clear();
            getline(cin, plain);
        }

        CTR_Mode<DES>::Encryption e;
        try
        {
            cout << "reading key from " << key_file << "..." << endl;
            FileSource(key_file, true,
                       new ArraySink(key, sizeof(key)));

            cout << "reading iv from " << iv_file << "..." << endl;
            FileSource(iv_file, true,
                       new ArraySink(iv, sizeof(iv)));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }

        e.SetKeyWithIV(key, sizeof(key), iv);

        decoded.clear();
        // time start
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < round_trip; i++)
        {
            cipher.clear();
            StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        }
        StringSource(cipher, true, new HexEncoder(new StringSink(decoded)));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double averageTime = static_cast<double>(duration) / round_trip_times;
        cout << "cipher: " << decoded << endl;
        cout << "Total times for encryption: " << averageTime << " ms" << std::endl;
        StringSource(decoded, true, new FileSink((char *)"cipher.txt"));
    }

    void decrypt() override
    {
        if (cipher_file != nullptr)
        {
            try
            {
                cout << "reading cipher text from " << cipher_file << "..." << endl;
                cipher.clear();
                FileSource(cipher_file, true,
                           new StringSink(cipher), false);
                cout << "cipher text: " << cipher << endl;
            }
            catch (const CryptoPP::Exception &e)
            {
                cerr << e.what() << endl;
                exit(1);
            }
        }
        else
        {
            char choice;
            cout << "Enter cipher text Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter cipher text (Hex format): ";
                cin >> cipher;
            }
            else
            {
                cipher = decoded;
            }
        }

        cout << "reading key from " << key_file << "..." << endl;
        FileSource(key_file, true,
                   new ArraySink(key, sizeof(key)));

        cout << "reading iv from " << iv_file << "..." << endl;
        FileSource(iv_file, true,
                   new ArraySink(iv, sizeof(iv)));

        string recovered;
        CTR_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);
        try
        {
            decoded.clear();
            // time start
            auto start = std::chrono::high_resolution_clock::now();
            StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
            for (int i = 0; i < round_trip; i++)
            {
                recovered.clear();
                StringSource s(decoded, true, new StreamTransformationFilter(d, new StringSink(recovered)));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            double averageTime = static_cast<double>(duration) / round_trip_times;
            cout << "recovered text: " << recovered << endl;
            cout << "Total times for decryptionn: " << averageTime << " ms" << std::endl;
            StringSource(decoded, true, new FileSink((char *)"recovered.txt"));
        }
        catch (const CryptoPP::Exception &e)
        {
            cerr << e.what() << endl;
            exit(1);
        }
    }
};

int main(int argc, char **argv)
{
    // Set locale to support UTF-8
#ifdef __linux__
    std::locale::global(std::locale("C.utf8"));
#endif

#ifdef _WIN32
    // Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    char *key_file = nullptr, *iv_file = nullptr, *plain_file = nullptr, *cipher_file = nullptr;
    std::set<string> modes = {"ECB", "ecb", "CBC", "cbc", "OFB", "ofb", "CFB", "cfb", "CTR", "ctr"};
    string mode;
    int opt;

    if (argc == 1)
    {
        cerr << "Usage: " << argv[0] << " -m mode [-k key_file] [-i iv_file] [-p plaintext_file] [-c ciphertext_file (hex)]";
        exit(1);
    }

    while ((opt = getopt(argc, argv, "m:k:i:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'm':
            if (modes.find(optarg) != modes.end())
            {
                mode = optarg;
                cout << "selected mode: " << optarg << endl;
            }
            else
            {
                cerr << "Invalid mode specified. Exiting program. Modes available:\n"
                     << "\tECB, CBC, OFB, CFB, CTR. " << endl;
                exit(1);
            }
            break;
        case 'k':
            key_file = optarg;
            break;
        case 'i':
            iv_file = optarg;
            break;
        case 'p':
            plain_file = optarg;
            break;
        case 'c':
            cipher_file = optarg;
            break;
        default: /* '?' */
            cerr << "Usage: " << argv[0] << " -m mode [-k key_file] [-i iv_file] [-p plaintext_file] [-c ciphertext_file]";
            exit(1);
        }
    }

    // Set default value for key_file and iv_file
    if (key_file == nullptr)
    {
        key_file = (char *)"key.bin";
    }
    if (iv_file == nullptr)
    {
        iv_file = (char *)"iv.bin";
    }

    Operation *operation = nullptr;
    if (mode == "ECB" || mode == "ecb")
    {
        operation = new ECB(key_file, iv_file, plain_file, cipher_file);
    }
    else if (mode == "CBC" || mode == "cbc")
    {
        operation = new CBC(key_file, iv_file, plain_file, cipher_file);
    }
    else if (mode == "OFB" || mode == "ofb")
    {
        operation = new OFB(key_file, iv_file, plain_file, cipher_file);
    }
    else if (mode == "CFB" || mode == "cfb")
    {
        operation = new CFB(key_file, iv_file, plain_file, cipher_file);
    }
    else if (mode == "CTR" || mode == "ctr")
    {
        operation = new CTR(key_file, iv_file, plain_file, cipher_file);
    }

    int descipher = 1;
    while (descipher > 0 && descipher < 4)
    {
        cout << "\nSelect key and iv generation, encryption or decryption message:\n"
             << "1-Key and iv generation;\n"
             << "2-Encryption;\n"
             << "3-Decryption;\n"
             << "others. exit.\n"
             << "Please enter your number: ";
        cin >> descipher;

        switch (descipher)
        {
        case 1:
        {
            operation->generate_key_iv(key_file, iv_file);
        }
        break;
        case 2:
        {
            operation->encrypt();
        }
        break;
        case 3:
        {
            operation->decrypt();
        }
        break;
        default:
            cout << "Exiting program." << endl;
            break;
        }
    }
    return 0;
}