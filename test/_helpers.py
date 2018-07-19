import multiprocessing


class AbnormalExitError(Exception):
    pass


def _call_worker(fn, pipe, *args, **kwargs):
    result = fn(*args, **kwargs)
    pipe.send(result)
    pipe.close()


def call_in_proc(fn, *args, **kwargs):
    rpipe, wpipe = multiprocessing.Pipe(duplex=False)
    proc = multiprocessing.Process(
        target=_call_worker, daemon=True,
        args=[fn, wpipe] + list(args), kwargs=kwargs,
    )
    proc.start()
    proc.join()
    if proc.exitcode != 0:
        raise AbnormalExitError(proc.exitcode)
    return rpipe.recv()
