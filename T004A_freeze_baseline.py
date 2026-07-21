"""Create a read-only local baseline snapshot of the four current GUI programs.

Place this script in the same directory as P001-P004 and run:

    python T004A_freeze_baseline.py

The script uses only the Python standard library. It never imports, executes,
or modifies the four programs. It copies them into a timestamped local folder,
calculates SHA-256 hashes, writes a local manifest, verifies the copies, and
prints one compact machine packet.
"""

from __future__ import annotations

import hashlib
import shutil
from datetime import datetime
from pathlib import Path


PROGRAMS = (
    "can_header_catalog_gui.py",
    "matlab_can_time_order_decoder_gui.py",
    "can_analysis_csv_cleaner_gui.py",
    "sre_cam_stage_residual_error_analyzer_v4_5_3_jp_compact_excel_notes.py",
)


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def checksum(values: list[int]) -> int:
    return sum(values) % 10


def main() -> int:
    base_dir = Path(__file__).resolve().parent
    source_paths = [base_dir / name for name in PROGRAMS]

    # Q1-Q4: each required source file exists.
    # 0 = internal error, 1 = missing, 2 = present.
    values = [2 if path.is_file() else 1 for path in source_paths]

    # Q5 snapshot created; Q6 all hashes match; Q7 manifest created;
    # Q8 unexpected/fatal error. Defaults represent not completed / no error.
    values.extend([0, 0, 0, 0])

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    snapshot_root = base_dir / "baseline_freeze_T004A"
    snapshot_dir = snapshot_root / timestamp
    manifest_path = snapshot_dir / "T004A_BASELINE_MANIFEST.txt"

    manifest_lines = [
        "T004A BASELINE MANIFEST",
        f"created_local={datetime.now().astimezone().isoformat()}",
        f"source_directory={base_dir}",
        f"snapshot_directory={snapshot_dir}",
        "",
    ]

    try:
        snapshot_dir.mkdir(parents=True, exist_ok=False)
        values[4] = 2

        all_match = True
        for source in source_paths:
            if not source.is_file():
                all_match = False
                manifest_lines.extend(
                    [
                        f"file={source.name}",
                        "status=MISSING",
                        "",
                    ]
                )
                continue

            original_hash_before = sha256_file(source)
            destination = snapshot_dir / source.name
            shutil.copy2(source, destination)
            copy_hash = sha256_file(destination)
            original_hash_after = sha256_file(source)
            matched = (
                original_hash_before == copy_hash == original_hash_after
            )
            all_match = all_match and matched

            manifest_lines.extend(
                [
                    f"file={source.name}",
                    f"original_sha256_before={original_hash_before}",
                    f"copy_sha256={copy_hash}",
                    f"original_sha256_after={original_hash_after}",
                    f"match={'YES' if matched else 'NO'}",
                    "",
                ]
            )

        values[5] = 2 if all_match else 1
        manifest_lines.append(
            f"all_required_files_match={'YES' if all_match else 'NO'}"
        )
        manifest_path.write_text("\n".join(manifest_lines), encoding="utf-8")
        values[6] = 2 if manifest_path.is_file() else 1
    except Exception as exc:  # The exact exception stays in the local manifest.
        values[7] = 1
        try:
            snapshot_dir.mkdir(parents=True, exist_ok=True)
            manifest_lines.extend(
                [
                    "",
                    "fatal_error=YES",
                    f"error_type={type(exc).__name__}",
                    f"error_message={exc}",
                ]
            )
            manifest_path.write_text("\n".join(manifest_lines), encoding="utf-8")
            values[6] = 2 if manifest_path.is_file() else values[6]
        except Exception:
            pass

    print("T004A1-2")
    print("A1-" + "".join(str(value) for value in values[:4]))
    print("A2-" + "".join(str(value) for value in values[4:8]))
    print(f"C-{checksum(values)}")

    return 0 if values[7] == 0 and values[5] == 2 else 1


if __name__ == "__main__":
    raise SystemExit(main())
