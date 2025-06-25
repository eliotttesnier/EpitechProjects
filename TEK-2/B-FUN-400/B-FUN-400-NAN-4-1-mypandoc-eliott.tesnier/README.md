# MyPandoc

MyPandoc is a Haskell-based document conversion tool that allows you to convert files between different formats such as XML, JSON, and Markdown*.

*as of now, markdown is only supported as output format

## Features

- Convert files between XML, JSON, and Markdown formats.
- Automatically detect the input format if not specified.
- Output the result to a file or standard output.

## Usage

Run the program using the following syntax:

```bash
./mypandoc -i ifile -f oformat [-o ofile] [-e iformat]
```

### Options

- `-i`: Path to the input file (mandatory).
- `-f`: Format of the output file (mandatory). Supported formats: `xml`, `json`, `markdown`.
- `-o`: Path to the output file (optional). If not provided, the result will be printed to the standard output.
- `-e`: Format of the input file (optional). If not provided, the program will attempt to detect the input format.

### Error Handling

- If no options or invalid options are provided, the program will return `84` and display a usage message along with an explicit error message.

## Example

### Input File (`example/example.xml`)

```xml
<document>
    <header title="Simple example"></header>
    <body>
        <paragraph>This is a simple example</paragraph>
    </body>
</document>
```

### Command

```bash
./mypandoc -f markdown -i example/example.xml
```

### Output

```markdown
---
title: Simple example
---

This is a simple example
```

## Notes

- Ensure that the input file exists and is in a supported format.
- The program is designed to handle common document structures and may not support all edge cases.
