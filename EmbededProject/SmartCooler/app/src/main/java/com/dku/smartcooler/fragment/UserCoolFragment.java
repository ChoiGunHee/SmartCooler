package com.dku.smartcooler.fragment;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

import com.dku.smartcooler.MainActivity;
import com.dku.smartcooler.R;
import com.dku.smartcooler.thread.ClientThread;


public class UserCoolFragment extends Fragment {

    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    private String mParam1;
    private String mParam2;

    private ClientThread thread;
    private MainActivity mainActivity;

    public UserCoolFragment() {
    }

    public static UserCoolFragment newInstance(String param1, String param2) {
        UserCoolFragment fragment = new UserCoolFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                              Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_usercool, container, false);

        mainActivity = (MainActivity) getActivity();
        thread = ((MainActivity) getActivity()).getClient();

        final EditText editText = (EditText) view.findViewById(R.id.editText);
        Button sendButton = (Button) view.findViewById(R.id.userSendbutton);
        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                thread.send(editText.getText()+"\0");
            }
        });
        return view;
    }

    public void onButtonPressed(Uri uri) {
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

    }

    @Override
    public void onDetach() {
        super.onDetach();

    }

}
