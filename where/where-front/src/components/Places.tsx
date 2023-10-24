/* eslint-disable */
import { useState, useMemo } from 'react';
import { Libraries, useLoadScript } from '@react-google-maps/api';
import styles from './Places.module.css';


import usePlacesAutocomplete, {
  getGeocode,
  getLatLng,
} from 'use-places-autocomplete';

import {
    Combobox,
    ComboboxInput,
    ComboboxList,
    ComboboxOption,
    ComboboxPopover,
} from "@reach/combobox";
import "@reach/combobox/styles.css";

interface PlacesAutocompleteProps {
  setSelected: (selected: any) => void;
  selected: any;
}

const libraries: Libraries = ['places'];

export default function Places(props: any) {

  const { isLoaded } = useLoadScript({
    googleMapsApiKey: import.meta.env.VITE_GOOGLE_MAPS_API_KEY,
    libraries: libraries,
  });

  if (!isLoaded) return <div>Loading...</div>;
  return <Map setSelect = {props.setSelect} />
}

function Map(props: any) {
  
  const center = useMemo(() => ({ lat: 43.45, lng: -80.49}), []);
  const [selected, setSelected] = useState<any>(null);

  return (
    <>
      <div className = { styles.placesContainer }>
        <PlacesAutocomplete setSelected={props.setSelect} selected = {selected}/>
      </div>
    </>
  );
}

const PlacesAutocomplete: React.FC<PlacesAutocompleteProps> = ({ setSelected }) => {
  const{
    ready,
    value,
    setValue,
    suggestions: { status, data },
    clearSuggestions
  } = usePlacesAutocomplete(); 

  const handleSelect = async (address: any) => {
    setValue(address, false)
    clearSuggestions();

    const results = await getGeocode({ address });
    const {lat, lng} = await getLatLng(results[0]);
    setSelected({address, lat, lng});
  }

  return <Combobox onSelect={handleSelect}>
    <ComboboxInput value = {value} onChange = {e => setValue(e.target.value)} disabled = {!ready} className = { styles.comboboxInput } placeholder = "Pesquise um Local"/>
    <ComboboxPopover>
      <ComboboxList>
        {status === "OK" && data.map(({place_id, description}) => (
          <ComboboxOption key = {place_id} value = {description} className = { styles.optionStyle }/>  
        ))}
      </ComboboxList>
    </ComboboxPopover>
  </Combobox>; 
};
