import io
import pytest

from pomodoro_timer import countdown_timer, run_pomodoro


def test_countdown_timer_short(monkeypatch, capsys):
    # make sleep a no-op so the test runs fast
    sleep_fn = lambda s: None
    clear_fn = lambda: None

    # Run a very short countdown and ensure the end message is printed
    countdown_timer(1, "TEST", 0, sleep_fn=sleep_fn, clear_fn=clear_fn, end_pause=0)

    out = capsys.readouterr().out
    assert "DING DING" in out or "is over" in out


def test_run_pomodoro_stops_after_max(monkeypatch):
    buffer = io.StringIO()

    def print_fn(*args, **kwargs):
        print(*args, file=buffer, **kwargs)

    sleep_fn = lambda s: None
    clear_fn = lambda: None

    # Run with tiny durations and a max pomodoro target
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
    assert "Reached target of 2 pomodoros" in contents
