#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/ec.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
// Define DLL export macro 
#ifndef DLL_EXPORT 
#ifdef _WIN32 
#define DLL_EXPORT __declspec(dllexport) 
#else 
#define DLL_EXPORT 
#endif 
#endif 
extern "C" {
    DLL_EXPORT bool generateECDSAKey(const char* privateKeyPath, const char* publicKeyPath);
    DLL_EXPORT bool generateRSAPSSKey(const char* privateKeyPath, const char* publicKeyPath);
    DLL_EXPORT bool signPdf(const char* privateKeyPath, const char* pdfPath, const char* signaturePath);
    DLL_EXPORT bool verifySignature(const char* publicKeyPath, const char* pdfPath, const char* signaturePath);
    DLL_EXPORT bool signPdfRSAPSS(const char* privateKeyPath, const char* pdfPath, const char* signaturePath);
    DLL_EXPORT bool verifySignatureRSAPSS(const char* publicKeyPath, const char* pdfPath, const char* signaturePath);
    // Implementations can go here if you're defining them within this block
}
// Function to generate ECDSA keys
bool generateECDSAKey(const std::string& privateKeyPath, const std::string& publicKeyPath) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    if (!ctx) {
        std::cerr << "Error creating context for ECDSA key generation." << std::endl;
        return false;
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Error initializing ECDSA key generation." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1) <= 0) {
        std::cerr << "Error setting curve for ECDSA key generation." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    EVP_PKEY *pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        std::cerr << "Error generating ECDSA key." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    EVP_PKEY_CTX_free(ctx);

    BIO *privBio = BIO_new_file(privateKeyPath.c_str(), "w");
    PEM_write_bio_PrivateKey(privBio, pkey, NULL, NULL, 0, NULL, NULL);
    BIO_free(privBio);

    BIO *pubBio = BIO_new_file(publicKeyPath.c_str(), "w");
    PEM_write_bio_PUBKEY(pubBio, pkey);
    BIO_free(pubBio);

    EVP_PKEY_free(pkey);
    return true;
}

// Function to generate RSASSA-PSS keys
bool generateRSAPSSKey(const std::string& privateKeyPath, const std::string& publicKeyPath) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        std::cerr << "Error creating context for RSA key generation." << std::endl;
        return false;
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Error initializing RSA key generation." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        std::cerr << "Error setting RSA key length." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    EVP_PKEY *pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        std::cerr << "Error generating RSA key." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    EVP_PKEY_CTX_free(ctx);

    BIO *privBio = BIO_new_file(privateKeyPath.c_str(), "w");
    PEM_write_bio_PrivateKey(privBio, pkey, NULL, NULL, 0, NULL, NULL);
    BIO_free(privBio);

    BIO *pubBio = BIO_new_file(publicKeyPath.c_str(), "w");
    PEM_write_bio_PUBKEY(pubBio, pkey);
    BIO_free(pubBio);

    EVP_PKEY_free(pkey);
    return true;
}

bool signPdf(const std::string& privateKeyPath, const std::string& pdfPath, const std::string& signaturePath) {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    BIO *keyData = BIO_new(BIO_s_file());
    BIO_read_filename(keyData, privateKeyPath.c_str());
    EVP_PKEY* privateKey = PEM_read_bio_PrivateKey(keyData, NULL, NULL, NULL);
    BIO_free(keyData);
    if (!privateKey) {
        std::cerr << "Error reading private key." << std::endl;
        ERR_print_errors_fp(stderr);
        return false;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::ifstream pdfFile(pdfPath, std::ios::binary);
    if (!pdfFile.is_open()) {
        std::cerr << "Error opening PDF file." << std::endl;
        return false;
    }
    std::vector<unsigned char> pdfContents((std::istreambuf_iterator<char>(pdfFile)), std::istreambuf_iterator<char>());
    pdfFile.close();

    SHA256(&pdfContents[0], pdfContents.size(), hash);

    auto start = std::chrono::high_resolution_clock::now();

    EVP_MD_CTX *mesData = EVP_MD_CTX_new();
    EVP_SignInit(mesData, EVP_sha256());
    EVP_SignUpdate(mesData, hash, SHA256_DIGEST_LENGTH);

    unsigned int signatureLen = EVP_PKEY_size(privateKey);
    std::vector<unsigned char> signature(signatureLen);
    if (!EVP_SignFinal(mesData, &signature[0], &signatureLen, privateKey)) {
        std::cerr << "Error signing PDF." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(privateKey);
        return false;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Sign operation took " << duration.count() << " seconds." << std::endl;

    std::ofstream signatureFile(signaturePath, std::ios::binary);
    if (!signatureFile.is_open()) {
        std::cerr << "Error opening signature file." << std::endl;
        return false;
    }
    signatureFile.write(reinterpret_cast<const char*>(&signature[0]), signatureLen);
    signatureFile.close();

    EVP_MD_CTX_free(mesData);
    EVP_PKEY_free(privateKey);
    EVP_cleanup();
    ERR_free_strings();
    return true;
}

bool verifySignature(const std::string& publicKeyPath, const std::string& pdfPath, const std::string& signaturePath) {
    BIO *pubData = BIO_new(BIO_s_file());
    if (BIO_read_filename(pubData, publicKeyPath.c_str()) <= 0) {
        std::cerr << "Error opening public key file." << std::endl;
        BIO_free(pubData);
        return false;
    }
    EVP_PKEY* publicKey = PEM_read_bio_PUBKEY(pubData, NULL, NULL, NULL);
    BIO_free(pubData);
    if (!publicKey) {
        std::cerr << "Error loading public key." << std::endl;
        return false;
    }

    std::ifstream pdfFile(pdfPath, std::ios::binary);
    std::vector<unsigned char> pdfContents((std::istreambuf_iterator<char>(pdfFile)), std::istreambuf_iterator<char>());
    pdfFile.close();

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(&pdfContents[0], pdfContents.size(), hash);

    std::ifstream signatureFile(signaturePath, std::ios::binary);
    std::vector<unsigned char> signature(std::istreambuf_iterator<char>(signatureFile), {});
    signatureFile.close();

    auto start = std::chrono::high_resolution_clock::now();

    EVP_MD_CTX *mesData = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(mesData, NULL, EVP_sha256(), NULL, publicKey);
    EVP_DigestVerifyUpdate(mesData, hash, SHA256_DIGEST_LENGTH);
    int result = EVP_DigestVerifyFinal(mesData, &signature[0], signature.size());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Verify operation took " << duration.count() << " seconds." << std::endl;

    EVP_MD_CTX_free(mesData);
    EVP_PKEY_free(publicKey);
    return result == 1;
}

bool signPdfRSAPSS(const std::string& privateKeyPath, const std::string& pdfPath, const std::string& signaturePath) {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    BIO *keyData = BIO_new(BIO_s_file());
    BIO_read_filename(keyData, privateKeyPath.c_str());
    EVP_PKEY* privateKey = PEM_read_bio_PrivateKey(keyData, NULL, NULL, NULL);
    BIO_free(keyData);
    if (!privateKey) {
        std::cerr << "Error reading private key." << std::endl;
        ERR_print_errors_fp(stderr);
        return false;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::ifstream pdfFile(pdfPath, std::ios::binary);
    if (!pdfFile.is_open()) {
        std::cerr << "Error opening PDF file." << std::endl;
        return false;
    }
    std::vector<unsigned char> pdfContents((std::istreambuf_iterator<char>(pdfFile)), std::istreambuf_iterator<char>());
    pdfFile.close();

    SHA256(&pdfContents[0], pdfContents.size(), hash);

    auto start = std::chrono::high_resolution_clock::now();

    EVP_MD_CTX *mesData = EVP_MD_CTX_new();
    EVP_PKEY_CTX *pkeyCtx = NULL;
    if (EVP_DigestSignInit(mesData, &pkeyCtx, EVP_sha256(), NULL, privateKey) <= 0) {
        std::cerr << "Error initializing signing." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(privateKey);
        return false;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(pkeyCtx, RSA_PKCS1_PSS_PADDING) <= 0) {
        std::cerr << "Error setting PSS padding." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(privateKey);
        return false;
    }
    size_t signatureLen;
    if (EVP_DigestSign(mesData, NULL, &signatureLen, hash, SHA256_DIGEST_LENGTH) <= 0) {
        std::cerr << "Error determining signature length." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(privateKey);
        return false;
    }

    std::vector<unsigned char> signature(signatureLen);
    if (EVP_DigestSign(mesData, &signature[0], &signatureLen, hash, SHA256_DIGEST_LENGTH) <= 0) {
        std::cerr << "Error signing PDF." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(privateKey);
        return false;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Sign operation took " << duration.count() << " seconds." << std::endl;

    std::ofstream signatureFile(signaturePath, std::ios::binary);
    if (!signatureFile.is_open()) {
        std::cerr << "Error opening signature file." << std::endl;
        return false;
    }
    signatureFile.write(reinterpret_cast<const char*>(&signature[0]), signatureLen);
    signatureFile.close();

    EVP_MD_CTX_free(mesData);
    EVP_PKEY_free(privateKey);
    EVP_cleanup();
    ERR_free_strings();
    return true;
}

bool verifySignatureRSAPSS(const std::string& publicKeyPath, const std::string& pdfPath, const std::string& signaturePath) {
    BIO *pubData = BIO_new(BIO_s_file());
    if (BIO_read_filename(pubData, publicKeyPath.c_str()) <= 0) {
        std::cerr << "Error opening public key file." << std::endl;
        BIO_free(pubData);
        return false;
    }
    EVP_PKEY* publicKey = PEM_read_bio_PUBKEY(pubData, NULL, NULL, NULL);
    BIO_free(pubData);
    if (!publicKey) {
        std::cerr << "Error loading public key." << std::endl;
        return false;
    }

    std::ifstream pdfFile(pdfPath, std::ios::binary);
    std::vector<unsigned char> pdfContents((std::istreambuf_iterator<char>(pdfFile)), std::istreambuf_iterator<char>());
    pdfFile.close();

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(&pdfContents[0], pdfContents.size(), hash);

    std::ifstream signatureFile(signaturePath, std::ios::binary);
    std::vector<unsigned char> signature(std::istreambuf_iterator<char>(signatureFile), {});
    signatureFile.close();

    auto start = std::chrono::high_resolution_clock::now();

    EVP_MD_CTX *mesData = EVP_MD_CTX_new();
    EVP_PKEY_CTX *pkeyCtx = NULL;
    if (EVP_DigestVerifyInit(mesData, &pkeyCtx, EVP_sha256(), NULL, publicKey) <= 0) {
        std::cerr << "Error initializing verification." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(publicKey);
        return false;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(pkeyCtx, RSA_PKCS1_PSS_PADDING) <= 0) {
        std::cerr << "Error setting PSS padding." << std::endl;
        EVP_MD_CTX_free(mesData);
        EVP_PKEY_free(publicKey);
        return false;
    }

    int result = EVP_DigestVerify(mesData, &signature[0], signature.size(), hash, SHA256_DIGEST_LENGTH);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Verify operation took " << duration.count() << " seconds." << std::endl;

    EVP_MD_CTX_free(mesData);
    EVP_PKEY_free(publicKey);
    return result == 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [sign|verify|genkey] [other parameters]" << std::endl;
        return 1;
    }
    std::string mode(argv[1]);

    if (mode == "genkey") {
        if (argc != 5) {
            std::cerr << "Usage: " << argv[0] << " genkey <ecdsa|rsa> <private key file> <public key file>" << std::endl;
            return 1;
        }
        std::string keyType = argv[2];
        const std::string privateKeyPath = argv[3];
        const std::string publicKeyPath = argv[4];
        if (keyType == "ecdsa") {
            if (generateECDSAKey(privateKeyPath, publicKeyPath)) {
                std::cout << "ECDSA key pair generated successfully." << std::endl;
            } else {
                std::cout << "Failed to generate ECDSA key pair." << std::endl;
            }
        } else if (keyType == "rsa") {
            if (generateRSAPSSKey(privateKeyPath, publicKeyPath)) {
                std::cout << "RSA key pair generated successfully." << std::endl;
            } else {
                std::cout << "Failed to generate RSA key pair." << std::endl;
            }
        } else {
            std::cerr << "Invalid key type specified." << std::endl;
            return 1;
        }
    } else if (mode == "sign") {
        if (argc != 6) {
            std::cerr << "Usage: " << argv[0] << " sign <ecdsa|rsa> <private key file> <PDF file> <signature output file>" << std::endl;
            return 1;
        }
        std::string keyType = argv[2];
        const std::string privateKeyPath = argv[3];
        const std::string pdfPath = argv[4];
        const std::string signaturePath = argv[5];
        if (keyType == "ecdsa") {
            if (signPdf(privateKeyPath, pdfPath, signaturePath)) {
                std::cout << "PDF signed successfully and saved signature to " << signaturePath << std::endl;
            } else {
                std::cout << "Failed to sign PDF." << std::endl;
            }
        } else if (keyType == "rsa") {
            if (signPdfRSAPSS(privateKeyPath, pdfPath, signaturePath)) {
                std::cout << "PDF signed successfully and saved signature to " << signaturePath << std::endl;
            } else {
                std::cout << "Failed to sign PDF." << std::endl;
            }
        } else {
            std::cerr << "Invalid key type specified." << std::endl;
            return 1;
        }
    } else if (mode == "verify") {
        if (argc != 6) {
            std::cerr << "Usage: " << argv[0] << " verify <ecdsa|rsa> <public key file> <PDF file> <signature file>" << std::endl;
            return 1;
        }
        std::string keyType = argv[2];
        const std::string publicKeyPath = argv[3];
        const std::string pdfPath = argv[4];
        const std::string signaturePath = argv[5];
        if (keyType == "ecdsa") {
            if (verifySignature(publicKeyPath, pdfPath, signaturePath)) {
                std::cout << "PDF verified successfully." << std::endl;
            } else {
                std::cout << "Failed to verify PDF." << std::endl;
            }
        } else if (keyType == "rsa") {
            if (verifySignatureRSAPSS(publicKeyPath, pdfPath, signaturePath)) {
                std::cout << "PDF verified successfully." << std::endl;
            } else {
                std::cout << "Failed to verify PDF." << std::endl;
            }
        } else {
            std::cerr << "Invalid key type specified." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Invalid mode specified." << std::endl;
        return 1;
    }
    return 0;
}
