#include <openssl/evp.h>
#include <openssl/err.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool encrypt_file(const std::string& inputFile, const std::string& outputFile, const std::string& password) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) return false;

    std::vector<unsigned char> plaintext((std::istreambuf_iterator<char>(in)), {});
    in.close();

    unsigned char key[32], iv[16]; // AES-256-CBC
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), nullptr,
        reinterpret_cast<const unsigned char*>(password.data()),
        password.size(), 1, key, iv);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    std::vector<unsigned char> ciphertext(plaintext.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    int len = 0, ciphertext_len = 0;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::ofstream out(outputFile, std::ios::binary);
    out.write(reinterpret_cast<char*>(ciphertext.data()), ciphertext_len);
    out.close();

    return true;
}

bool decrypt_file(const std::string& inputFile, const std::string& outputFile, const std::string& password) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) return false;

    std::vector<unsigned char> ciphertext((std::istreambuf_iterator<char>(in)), {});
    in.close();

    unsigned char key[32], iv[16];
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), nullptr,
        reinterpret_cast<const unsigned char*>(password.data()),
        password.size(), 1, key, iv);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    std::vector<unsigned char> plaintext(ciphertext.size());
    int len = 0, plaintext_len = 0;

    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size());
    plaintext_len = len;
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) <= 0) {
        EVP_CIPHER_CTX_free(ctx);
        return false; // неверный пароль или поврежден файл
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::ofstream out(outputFile, std::ios::binary);
    out.write(reinterpret_cast<char*>(plaintext.data()), plaintext_len);
    out.close();

    return true;
}
