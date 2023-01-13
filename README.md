# Filesystem Simulator

This is a command line filesystem simulator application written in C. It allows users to create and manage directories and files. The application supports the following commands:
- `ls` to display the contents of a directory
- `rm` to delete a directory or file
- `mkdir` to create a directory
- `mkfile` to create a file
- `cpfile` to copy a file
- `cpdir` to copy a directory
- `exist` to search for a directory or file

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You will need a C compiler to run the program.

### Installing

Clone or download the repository to your local machine.

### Running the program

Compile the program using your C compiler.

```bash
gcc SGF.c SGF_HEADER.c -o SGF
```

Then run the compiled program :

```bash
./SGF
```

## Usage

Chose whether to load existing filesystem structure or initialize the default structure : 

![screenshot-1](https://drive.google.com/uc?export=view&id=19IFROdldKujEHzSwatudw7ftnU_S8v2_) 

Enter storage size :

![screenshot-1](https://drive.google.com/uc?export=view&id=196C_RfQylEg8dceMZO9xyEBvwLD_SAIW) 

The filesystem tree will be displayed as well as storage informations :

![screenshot-1](https://drive.google.com/uc?export=view&id=19GjnNcnW-ym8Ii0DyqwuIgnN9bd79-_V) 

Enter any of the following commands :

- `ls` - Display the contents of a directory

- `rm` - Delete a directory or file

- `mkdir` - Create a new directory

- `mkfile` - Create a new file

- `cpfile` - Copy a file

- `cpdir` - Copy a directory

- `exist` - Search for a directory or file

Example of using `ls` command :

![screenshot-1](https://drive.google.com/uc?export=view&id=18gm6HqkyvN-q__B8R7ECNQeMaK2NvHnz) 

## Limitations

- The program currently is not supporting loading saved filesystem structures


## License

This project is licensed under the MIT License.
