# Code Study

Small programming exercises with runnable examples and sample data.

## CSV statistics in Python

Practice reading a CSV file, selecting a column, and calculating basic statistics
with the Python standard library. No third-party packages are required.

```sh
python examples/csv_stats.py data/study_minutes.csv minutes
```

Use `python3` if that is the Python command on your system. Run the command from
the repository root.

Expected output:

```text
Count: 7
Minimum: 10
Maximum: 45
Mean: 30
```

The sample contains fictional study times. The selected column must contain a
number in every row.

## Exercises

- Add a median to the output using `statistics.median`.
- Try another numeric column in a different CSV file.
- Group the rows by a category before calculating statistics.
