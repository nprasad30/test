    streamlit run recruitapp.py [ARGUMENTS]
2024-09-12 17:15:00.739 Session state does not function when running a script without `streamlit run`
Traceback (most recent call last):
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state.py", line 398, in __getitem__
    return self._getitem(widget_id, key)
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state.py", line 443, in _getitem
    raise KeyError
KeyError

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state_proxy.py", line 119, in __getattr__
    return self[key]
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state_proxy.py", line 90, in __getitem__
    return get_session_state()[key]
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/safe_session_state.py", line 91, in __getitem__
    return self._state[key]
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state.py", line 400, in __getitem__
    raise KeyError(_missing_key_error_message(key))
KeyError: 'st.session_state has no key "conversation_history". Did you forget to initialize it? More info: https://docs.streamlit.io/library/advanced-features/session-state#initialization'

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/Users/nivipr/Downloads/recruitapp.py", line 102, in <module>
    main()
  File "/Users/nivipr/Downloads/recruitapp.py", line 65, in main
    for i, (role, text) in enumerate(st.session_state.conversation_history):
  File "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/streamlit/runtime/state/session_state_proxy.py", line 121, in __getattr__
    raise AttributeError(_missing_attr_error_message(key))
AttributeError: st.session_state has no attribute "conversation_history". Did you forget to initialize it? More info: https://docs.streamlit.io/library/advanced-features/session-state#initialization
nivipr@3c063014d717 Downloads % 
