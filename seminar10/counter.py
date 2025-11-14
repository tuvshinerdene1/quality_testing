import re
import math
from collections import Counter
import sys

def tokenize_line(line, in_block_comment):
    if in_block_comment[0]:
        if '*/' in line:
            line = line[line.index('*/') + 2:]
            in_block_comment[0] = False
        else:
            return []
    if '//' in line:
        line = line[:line.index('//')]
    if '/*' in line:
        in_block_comment[0] = True
        line = line[:line.index('/*')]
    if not line.strip():
        return []

    tokens = []
    i = 0
    in_string = False
    string_start = None
    while i < len(line):
        if in_string:
            if line[i] == '"':
                in_string = False
                string_content = line[string_start:i]
                format_specifiers = re.findall(r'%[df]', string_content)
                tokens.extend(format_specifiers)
                i += 1
                continue
            i += 1
        else:
            if line[i] == '"':
                in_string = True
                string_start = i + 1
                i += 1
                continue
            match = re.match(
                r'(&\w+|\w+|[+\-*/=<>!&|%^?:;,.()\[\]\{\}]|==|!=|<=|>=|&&|\|\||\+\+|--|\+=|-=|\*=|/=|<<|>>)',
                line[i:]
            )
            if match:
                token = match.group(0)
                if token.startswith('&') and token[1:].isalnum():
                    tokens.append('&')
                    tokens.append(token[1:])
                else:
                    tokens.append(token)
                i += len(token)
            else:
                i += 1
    return tokens

def calculate_details(n1, n2, N1, N2):
    n = n1 + n2
    print(f"n (Program Vocabulary) = {n}")
    N = N1 + N2
    print(f"N (Program Length) = {N}")
    V = N * math.log2(n) if n > 0 else 0
    print(f"V (Volume) = {V:.2f}")
    D = (n1 / 2) * (N2 / n2) if n2 > 0 else 0 
    print(f"D (Difficulty) = {D:.2f}")
    E = D * V 
    print(f"E (Effort) = {E:.2f}")
    T = E / 18
    print(f"T (Time, seconds) = {T:.2f}")
    B = math.pow(E, 2/3) / 3000
    print(f"B (Estimated Bugs) = {B:.2f}")

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    operators = {
        '(', ')', '{', '}', '[', ']', ';', ',', '=', '+', '-', '*', '/',
        '&', '|', '^', '!', '~', '<', '>', '?', ':', '.', '++', '--',
        '+=', '-=', '*=', '/=', '<<', '>>', '<=', '>=', '==', '!=', '&&', '||', '%',
        '&'
    }
    keywords = {
        'main', 'int', 'scanf', 'printf', 'return', 'for', 'while', 'if',
        'else', 'struct', 'enum', 'typedef', 'cout', 'cin', 'continue', 'break', 'endl', 'namespace','using'
    }
    token_counts = Counter()
    operand_counts = Counter()
    in_block_comment = [False]

    try:
        with open(filename, 'r') as file:
            all_tokens = []
            for line in file:
                tokens = tokenize_line(line, in_block_comment)
                all_tokens.extend(tokens)
    except FileNotFoundError:
        print(f"Error: Could not open file {filename}")
        sys.exit(1)

    open_paren = close_paren = open_brace = close_brace = 0
    for token in all_tokens:
        if token == '(':
            open_paren += 1
        elif token == ')':
            close_paren += 1
        elif token == '{':
            open_brace += 1
        elif token == '}':
            close_brace += 1
        elif token in operators or token in keywords:
            token_counts[token] += 1
        else:
            operand_counts[token] += 1


    token_counts['()'] = min(open_paren, close_paren)
    token_counts['{}'] = min(open_brace, close_brace)

    for single_token in ['(', ')', '{', '}']:
        if single_token in token_counts:
            del token_counts[single_token]

    n1 = len([t for t, c in token_counts.items() if c > 0])
    n2 = len([t for t, c in operand_counts.items() if c > 0])
    N1 = sum(token_counts.values())
    N2 = sum(operand_counts.values())

    # Print results
    # print("\n--- Operand Counts ---")
    # for token, count in sorted(operand_counts.items()):
    #     if count > 0:
    #         print(f"{token} = {count}")

    # print("\n--- Operator and Keyword Counts ---")
    # for token, count in sorted(token_counts.items()):
    #     if count > 0:
    #         print(f"{token} = {count}")

    print(f"n1: {n1}")
    print(f"n2: {n2}")
    print(f"N1: {N1}")
    print(f"N2: {N2}")

    # Calculate and print Halstead metrics
    calculate_details(n1, n2, N1, N2)

if __name__ == "__main__":
    main()