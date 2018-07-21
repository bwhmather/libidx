import multiprocessing


def _call_worker(fn, pipe, *args, **kwargs):
    try:
        result = fn(*args, **kwargs)
    except Exception as error:
        pipe.send((None, error))
    else:
        pipe.send((result, None))
    pipe.close()


def call_in_proc(fn, *args, **kwargs):
    rpipe, wpipe = multiprocessing.Pipe(duplex=False)
    proc = multiprocessing.Process(
        target=_call_worker, daemon=True,
        args=[fn, wpipe] + list(args), kwargs=kwargs,
    )
    proc.start()
    proc.join()
    if proc.exitcode == -6:
        raise AssertionError("c assertion failed")
    if proc.exitcode != 0:
        raise RuntimeError((
            "subprocedure exited with exit code {code}"
        ).format(code=proc.exitcode))

    result, error = rpipe.recv()
    if error:
        raise error
    return result
