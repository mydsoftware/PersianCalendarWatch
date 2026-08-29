#!/usr/bin/env python3
"""دریافت داده تقویم و مناسبت‌ها از Time.ir برای بسته‌بندی آفلاین در ساعت.

این ابزار روی کامپیوتر/CI اجرا می‌شود؛ خود Galaxy Watch مستقیماً Time.ir را scrape نمی‌کند.
"""
import json
import re
from pathlib import Path
from urllib.request import Request, urlopen
from html import unescape

URL = "https://www.time.ir/event-year"
OUT = Path(__file__).resolve().parents[1] / "data" / "timeir-events.json"
MONTHS = [
    "فروردین", "اردیبهشت", "خرداد", "تیر", "اَمرداد", "شهریور",
    "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"
]


def strip_html(value: str) -> str:
    value = re.sub(r"<[^>]+>", " ", value)
    value = unescape(value)
    return re.sub(r"\s+", " ", value).strip()


def fetch() -> str:
    req = Request(URL, headers={"User-Agent": "PersianCalendarWatch/1.0"})
    with urlopen(req, timeout=30) as response:
        return response.read().decode("utf-8", errors="replace")


def parse(html: str):
    # متن صفحه سالانه Time.ir را به شکل پایدار و ساده استخراج می‌کنیم.
    text = strip_html(html)
    events = []
    current_month = None

    for line in re.split(r"\n+", text):
        line = line.strip()
        for month in MONTHS:
            if month in line and len(line) < 40:
                current_month = month
                break

        m = re.match(r"^(\d{1,2})\s+(.+)$", line)
        if current_month and m:
            day = int(m.group(1))
            title = m.group(2).strip()
            if 1 <= day <= 31 and title:
                events.append({
                    "month": current_month,
                    "day": day,
                    "title": title,
                    "source": "Time.ir"
                })

    # حذف موارد تکراری ناشی از ساختار HTML صفحه
    unique = {(x["month"], x["day"], x["title"]): x for x in events}
    return list(unique.values())


def main():
    html = fetch()
    data = {
        "source": "https://www.time.ir/event-year",
        "generated_by": "tools/timeir_sync.py",
        "events": parse(html),
    }
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"Wrote {len(data['events'])} events to {OUT}")


if __name__ == "__main__":
    main()
