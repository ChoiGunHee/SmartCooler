package com.dku.smartcooler.fragment;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.dku.smartcooler.MainActivity;
import com.dku.smartcooler.R;
import com.dku.smartcooler.thread.ClientThread;

import java.util.ArrayList;

public class CoolListFragment extends Fragment {

    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    private String mParam1;
    private String mParam2;

    private ClientThread thread;
    private MainActivity mainActivity;

    public CoolListFragment() {
    }

    public static CoolListFragment newInstance(String param1, String param2) {
        CoolListFragment fragment = new CoolListFragment();
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
        View view = inflater.inflate(R.layout.fragment_coollist, container, false);

        mainActivity = (MainActivity) getActivity();
        thread = ((MainActivity) getActivity()).getClient();

        ListView listView = (ListView) view.findViewById(R.id.menuList);

        final ArrayList<String> list = new ArrayList<String>();
        list.add("커피");
        list.add("이유식");
        list.add("홍차");

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(view.getContext(), android.R.layout.simple_list_item_1, list);

        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {

                String menu = list.get(i);
                int menuTemperature = -1;

                if(menu.equals("커피")) {
                    menuTemperature = 45;
                } else if(menu.equals("이유식")) {
                    menuTemperature = 60;
                } else if(menu.equals("홍차")) {
                    menuTemperature = 50;
                }

                thread.send(menuTemperature+"\0");
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
