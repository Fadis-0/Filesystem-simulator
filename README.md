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

```gcc SGF.c SGF_HEADER.c -o SGF```

Then run the compiled program with the storage size and command as arguments:

```./SGF [storage size] [command] [command arguments]```

## Usage

`ls [directory address] [directory name]` - Display the contents of a directory

`rm [directory address/file address] [directory/file name]` - Delete a directory or file

`mkdir [directory address] [directory name]` - Create a new directory

`mkfile [directory address] [file name] [file size]` - Create a new file

`cpfile [source file address] [source file name] [destination address] [destination file name]` - Copy a file

`cpdir [source directory address] [source directory name] [destination address] [destination directory name]` - Copy a directory

`exist [directory/file name]` - Search for a directory or file



## Limitations

- The program currently only support one level deep directory tree
- The program currently only support one level deep file tree


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

*Feel free to customize or add more information as you see fit*
