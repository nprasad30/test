import streamlit as st
import boto3

bedrock_agent_runtime = boto3.client('bedrock-agent-runtime')
AGENT_ID = 'your-agent-id'  # Replace with your actual Agent ID
AGENT_ALIAS_ID = 'your-agent-alias-id'  # Replace with your actual Agent Alias ID

def invoke_agent(input_text, conversation_history, enable_trace=False):
    try:
        full_input = f"Conversation history:\n{conversation_history}\n\nUser: {input_text}"
        response = bedrock_agent_runtime.invoke_agent(
            agentId=AGENT_ID,
            agentAliasId=AGENT_ALIAS_ID,
            sessionId='recruitment-session',
            inputText=full_input,
            enableTrace=enable_trace
        )
        
        event_stream = response['completion']
        full_response = ""
        trace = []
        for event in event_stream:
            if 'chunk' in event:
                chunk = event['chunk']
                if 'bytes' in chunk:
                    full_response += chunk['bytes'].decode('utf-8')
            if enable_trace and 'trace' in event:
                trace.append(event['trace'])
        
        return full_response.strip(), trace
    except Exception as e:
        st.error(f"Error invoking agent: {str(e)}")
        return None, None

def main():
    st.title('AI Recruitment Assistant')
    
    with st.sidebar:
        enable_trace = st.toggle('Enable Reasoning Trace', value=False)
    
    st.markdown("""
    Examples of queries you can ask:
    - Generate a job description for a Software Engineer at TechCorp
    - Create interview questions for a Marketing Manager position
    - What are best practices for conducting a remote interview?
    - Post the job description we just created
    
    Enter your query below:
    """)
    
    # Initialize conversation history in session state if it doesn't exist
    if 'conversation_history' not in st.session_state:
        st.session_state.conversation_history = []
    
    # Display conversation history
    for role, text in st.session_state.conversation_history:
        with st.chat_message(role):
            st.markdown(text)
    
    # Get user input
    user_input = st.chat_input("Type your message here...")
    
    if user_input:
        # Add user message to chat history
        st.session_state.conversation_history.append(("user", user_input))
        with st.chat_message("user"):
            st.markdown(user_input)
        
        # Get AI response
        with st.spinner('AI Assistant is thinking...'):
            conversation_text = "\n".join([f"{role}: {text}" for role, text in st.session_state.conversation_history])
            ai_response, trace = invoke_agent(user_input, conversation_text, enable_trace)
        
        if ai_response:
            # Add AI response to chat history
            st.session_state.conversation_history.append(("assistant", ai_response))
            with st.chat_message("assistant"):
                st.markdown(ai_response)
            
            if enable_trace and trace:
                with st.expander("View Reasoning Trace"):
                    st.json(trace)
        else:
            st.warning("No response received. Please try again.")

if __name__ == "__main__":
    main()
