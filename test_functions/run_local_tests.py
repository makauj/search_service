import io
import sys

from pomodoro_timer import countdown_timer, run_pomodoro


def assert_in(haystack, needle, msg=None):
    if needle not in haystack:
        raise AssertionError(msg or f"Expected '{needle}' in output")


def test_countdown_timer_short():
    sleep_fn = lambda s: None
    clear_fn = lambda: None

    # Capture stdout
    buf = io.StringIO()
    def print_fn(*args, **kwargs):
        print(*args, file=buf, **kwargs)

    countdown_timer(1, "TEST", 0, sleep_fn=sleep_fn, clear_fn=clear_fn, print_fn=print_fn, end_pause=0)

    out = buf.getvalue()
    assert_in(out, "DING DING")


def test_run_pomodoro_stops_after_max():
    buffer = io.StringIO()
    def print_fn(*args, **kwargs):
        print(*args, file=buffer, **kwargs)

    sleep_fn = lambda s: None
    clear_fn = lambda: None

    run_pomodoro(
        work_sec=1,
        short_sec=1,
        long_sec=1,
        pomodoros_per_cycle=2,
        max_pomodoros=2,
        sleep_fn=sleep_fn,
        clear_fn=clear_fn,
        print_fn=print_fn,
    )

    contents = buffer.getvalue()
    assert_in(contents, "Reached target of 2 pomodoros")


if __name__ == '__main__':
    tests = [
        test_countdown_timer_short,
        test_run_pomodoro_stops_after_max,
    ]
    failures = 0
    for t in tests:
        try:
            t()
            print(f"PASS: {t.__name__}")
        except AssertionError as e:
            print(f"FAIL: {t.__name__} - {e}")
            failures += 1
        except Exception as e:
            print(f"ERROR: {t.__name__} - {e}")
            failures += 1

    if failures:
        print(f"{failures} tests failed")
        sys.exit(1)
    else:
        print("All local tests passed")
        sys.exit(0)
