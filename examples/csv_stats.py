"""Print basic statistics for a numeric CSV column."""

import argparse
import csv
from statistics import mean


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("csv_file", help="Path to a CSV file with a header row")
    parser.add_argument("column", help="Name of the numeric column")
    args = parser.parse_args()

    with open(args.csv_file, encoding="utf-8-sig", newline="") as source:
        reader = csv.DictReader(source)
        if args.column not in (reader.fieldnames or []):
            parser.error(f"Column not found: {args.column}")
        values = [float(row[args.column]) for row in reader]

    if not values:
        parser.error("The CSV contains no data rows.")

    print(f"Count: {len(values)}")
    print(f"Minimum: {min(values):g}")
    print(f"Maximum: {max(values):g}")
    print(f"Mean: {mean(values):g}")


if __name__ == "__main__":
    main()
