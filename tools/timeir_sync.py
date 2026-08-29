#!/usr/bin/env python3
"""ساخت دیتای محلی تقویم از Time.ir.

این ابزار روی PC/CI اجرا می‌شود و خروجی JSON را برای استفاده آفلاین روی ساعت
تولید می‌کند. خود Galaxy Watch مستقیماً Time.ir را scrape نمی‌کند.
"""
from __future__ import annotations
import argparse, json, re
from datetime import datetime, timezone
from html import unescape
from pathlib import Path
from urllib.request import Request, urlopen

URL = "https://www.time.ir/event-year"
ROOT = Path(__file__).resolve().parents[1]
MONTHS = ["فروردین", "اردیبهشت", "خرداد", "تیر", "اَمرداد", "مرداد", "شهریور", "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"]


def strip_html(value: str) -> str:
    value = re.sub(r"<[^>]+>", "\n", value)
    return re.sub(r"[ \t\r\f\v]+", " ", unescape(value))


def fetch() -> str:
    req = Request(URL, headers={"User-Agent": "PersianCalendarWatch/1.0"})
    with urlopen(req, timeout=30) as response:
        return response.read().decode("utf-8", errors="replace")


def parse(html: str, year: int) -> list[dict]:
    text = strip_html(html)
    events, current_month = [], None
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        for month in MONTHS:
            if month in line and len(line) < 40:
                current_month = month
                break
        m = re.match(r"^(\d{1,2})\s+(.+)$", line)
        if current_month and m:
            day, title = int(m.group(1)), m.group(2).strip()
            if 1 <= day <= 31 and title:
                events.append({"month": current_month, "day": day, "title": title, "source": "Time.ir"})
    return list({(x["month"], x["day"], x["title"]): x for x in events}.values())


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--year", type=int, default=1405)
    args = parser.parse_args()
    data = {
        "schema_version": 1,
        "source": URL,
        "calendar": "jalali",
        "year": args.year,
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "events": parse(fetch(), args.year),
    }
    out = ROOT / "data" / f"calendar-{args.year}.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"Wrote {len(data['events'])} events to {out}")


if __name__ == "__main__":
    main()
