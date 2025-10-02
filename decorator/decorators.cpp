#include <iostream>
#include <string>

class DataStream
{
public:
    virtual ~DataStream()=default;
    virtual void write(const std::string& data)=0;
    virtual std::string read()=0;
};

class FileStream : public DataStream
{
    std::string storage;
public:
    void write(const std::string& data) override
    {
        storage=data;
    }

    std::string read() override
    {
        return storage;
    }
};

class DataStreamDecorator : public DataStream
{
protected:
    DataStream* wrap;
public:
    DataStreamDecorator(DataStream* stream) : wrap(stream)
    {}

    void write(const std::string& data) override
    {
        wrap->write(data);
    }
    std::string read() override
    {
        return wrap->read();
    }    
};

class EncryptionDecoder: public DataStreamDecorator
{
private:
    int shift;
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);

public:
    EncryptionDecoder(DataStream* stream, int encshift=3): DataStreamDecorator(stream), shift(encshift)
    {}

    void write(const std::string& data) override;
    std::string read() override;
};

std::string EncryptionDecoder::encrypt(const std::string& data)
{
    std::string result = data;
    for (char& c : result)
    {
        if (c >= 'a' && c <= 'z')
            c = ((c - 'a' + shift) % 26) + 'a';
        else if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' + shift) % 26) + 'A';
        // Non-alphabetic characters unchanged
    }
    return result;
}

std::string EncryptionDecoder::decrypt(const std::string& data)
{
    std::string result = data;
    for (char& c : result)
    {
        if (c >= 'a' && c <= 'z')
            c = ((c - 'a' - shift + 26) % 26) + 'a';
        else if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' - shift + 26) % 26) + 'A';
        // Non-alphabetic characters unchanged
    }
    return result;
}
void EncryptionDecoder::write(const std::string& data)
{
    std::string encryptedData = encrypt(data);
    wrap->write(encryptedData);
}

std::string EncryptionDecoder::read()
{
    std::string encryptedData = wrap->read();
    return decrypt(encryptedData);
}

int main()
{
    FileStream file;
    EncryptionDecoder encryptedStream(&file, 3); // shift = 3

    std::string original = "HelloWorld";
    encryptedStream.write(original);

    std::cout << "Encrypted stored data: " << file.read() << std::endl;
    std::cout << "Decrypted read data: " << encryptedStream.read() << std::endl;

    return 0;
}
