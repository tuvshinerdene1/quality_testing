#!/usr/bin/env python3
import re
import sys
import math
from collections import Counter

class HalsteadCalculator:
    def __init__(self):
        self.keywords = {
            'auto', 'break', 'case', 'char', 'const', 'continue', 'default',
            'do', 'double', 'else', 'enum', 'extern', 'float', 'for', 'goto',
            'if', 'int', 'long', 'register', 'return', 'short', 'signed',
            'sizeof', 'static', 'struct', 'switch', 'typedef', 'union',
            'unsigned', 'void', 'volatile', 'while', 'class', 'namespace',
            'template', 'public', 'private', 'protected', 'virtual', 'friend',
            'inline', 'operator', 'this', 'new', 'delete', 'bool', 'true', 'false',
            'include', 'define', 'ifdef', 'ifndef', 'endif'
        }
        
        self.operators = {
            '+', '-', '*', '/', '%', '=', '==', '!=', '<', '>', '<=', '>=',
            '++', '--', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=',
            '<<', '>>', '<<=', '>>=', '&&', '||', '!', '&', '|', '^', '~',
            '?', ':', '->', '.', '::', '(', ')', '{', '}', '[', ']', ';', 
            ',', '#'
        }
        
        self.operator_counts = Counter()
        self.operand_counts = Counter()
    
    def remove_comments(self, code):
        """Remove single-line and multi-line comments"""
        # Remove multi-line comments
        code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
        # Remove single-line comments
        code = re.sub(r'//.*?$', '', code, flags=re.MULTILINE)
        return code
    
    def remove_strings(self, code):
        """Replace string and char literals with placeholders"""
        # Replace string literals
        code = re.sub(r'"([^"\\]|\\.)*"', '"%STRING%"', code)
        # Replace character literals
        code = re.sub(r"'([^'\\]|\\.)'", "'%CHAR%'", code)
        return code
    
    def tokenize(self, code):
        """Tokenize the code into operators and operands"""
        # Remove comments and strings
        code = self.remove_comments(code)
        original_code = code
        code = self.remove_strings(code)
        
        # Pattern to match tokens
        # Matches: multi-char operators, single-char operators, identifiers, numbers
        pattern = r'(->|<<|>>|\+\+|--|<=|>=|==|!=|\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=|&&|\|\||::|[+\-*/%=<>!&|^~?:.,;(){}\[\]#]|[a-zA-Z_]\w*|\d+\.?\d*[eE]?[+-]?\d*[fFlLuU]*|"%STRING%"|\'%CHAR%\')'
        
        tokens = re.findall(pattern, code)
        
        for token in tokens:
            self.classify_token(token)
    
    def classify_token(self, token):
        """Classify token as operator or operand"""
        # Skip empty tokens
        if not token or token.isspace():
            return
        
        # Keywords and operators are operators in Halstead metrics
        if token in self.keywords or token in self.operators:
            self.operator_counts[token] += 1
        # Preprocessor directives
        elif token.startswith('#'):
            self.operator_counts[token] += 1
        # String/char literals are operands
        elif token in ['"%STRING%"', "'%CHAR%'"]:
            self.operand_counts[token] += 1
        # Numbers are operands
        elif re.match(r'^\d', token):
            self.operand_counts[token] += 1
        # Identifiers (variables, functions) are operands
        elif re.match(r'^[a-zA-Z_]', token):
            self.operand_counts[token] += 1
    
    def calculate_metrics(self):
        """Calculate Halstead complexity metrics"""
        n1 = len(self.operator_counts)  # Distinct operators
        n2 = len(self.operand_counts)   # Distinct operands
        N1 = sum(self.operator_counts.values())  # Total operators
        N2 = sum(self.operand_counts.values())   # Total operands
        
        n = n1 + n2  # Program vocabulary
        N = N1 + N2  # Program length
        
        # Calculate derived metrics
        V = N * math.log2(n) if n > 0 else 0  # Volume
        D = (n1 / 2) * (N2 / n2) if n2 > 0 else 0  # Difficulty
        E = D * V  # Effort
        T = E / 18  # Time (seconds)
        
        return {
            'n1': n1, 'N1': N1,
            'n2': n2, 'N2': N2,
            'n': n, 'N': N,
            'V': V, 'D': D, 'E': E, 'T': T
        }
    
    def analyze_file(self, filename):
        """Analyze a source file"""
        try:
            with open(filename, 'r', encoding='utf-8') as f:
                code = f.read()
        except FileNotFoundError:
            print(f"Error: File '{filename}' not found")
            sys.exit(1)
        except Exception as e:
            print(f"Error reading file: {e}")
            sys.exit(1)
        
        self.tokenize(code)
        metrics = self.calculate_metrics()
        self.print_results(metrics)
    
    def print_results(self, metrics):
        """Print detailed results"""
        print("\n=== HALSTEAD METRICS ===\n")
        
        print("--- Operators ---")
        for op, count in sorted(self.operator_counts.items()):
            print(f"  {op:15} : {count}")
        print(f"\nDistinct Operators (n1): {metrics['n1']}")
        print(f"Total Operators (N1): {metrics['N1']}")
        
        print("\n--- Operands ---")
        for operand, count in sorted(self.operand_counts.items()):
            print(f"  {operand:15} : {count}")
        print(f"\nDistinct Operands (n2): {metrics['n2']}")
        print(f"Total Operands (N2): {metrics['N2']}")
        
        print("\n--- Calculated Metrics ---")
        print(f"Program Vocabulary (n = n1 + n2): {metrics['n']}")
        print(f"Program Length (N = N1 + N2): {metrics['N']}")
        print(f"Volume (V = N * log2(n)): {metrics['V']:.2f}")
        print(f"Difficulty (D = (n1/2) * (N2/n2)): {metrics['D']:.2f}")
        print(f"Effort (E = D * V): {metrics['E']:.2f}")
        print(f"Time to Program (T = E/18 seconds): {metrics['T']:.2f} seconds")
        print(f"Time to Program: {metrics['T']/60:.2f} minutes")

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <filename>")
        sys.exit(1)
    
    calculator = HalsteadCalculator()
    calculator.analyze_file(sys.argv[1])

if __name__ == "__main__":
    main()