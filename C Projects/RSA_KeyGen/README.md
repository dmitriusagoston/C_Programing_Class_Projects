# asignment 6
The purpose of this program is to create a key that will be used for the encryption and decryption of files. This process is done through three main functions. Those being, the creation of a key using a key generator, and then both the encryption and the decryption of the desired files using the generated key. First the key generator is given the task of creating RSA public and private key pairs. With these key pairs generated, the encrypter uses the public key in order to encrypt the given files. The decrypter can then use the corresponding private key to decrypt the previously encrypted files. 

# building
To build this program:
- clone this repo
- cd into cse13s/asgn6/
- make

# running
To run this program:

USAGE
./keygen [-hv] [-b bits] -n pbfile -d pvfile

OPTIONS
- -h             Display program help and usage.
- -v             Display verbose program output.
- -b bits        Minimum bits needed for public key n (default: 256).
- -i confidence  Miller-Rabin iterations for testing primes (default: 50).
- -n pbfile      Public key file (default: rsa.pub).
- -d pvfile      Private key file (default: rsa.priv).
- -s seed        Random seed for testing.

USAGE
./encrypt [-hv] [-i infile] [-o outfile] -n pubkey

OPTIONS
- -h             Display program help and usage.
- -v             Display verbose program output.
- -i infile      Input file of data to encrypt (default: stdin).
- -o outfile     Output file for encrypted data (default: stdout).
- -n pbfile      Public key file (default: rsa.pub).

USAGE
./encrypt [-hv] [-i infile] [-o outfile] -n privkey

OPTIONS
- -h             Display program help and usage.
- -v             Display verbose program output.
- -i infile      Input file of data to encrypt (default: stdin).
- -o outfile     Output file for encrypted data (default: stdout).
- -n pbfile      Private key file (default: rsa.pub).
