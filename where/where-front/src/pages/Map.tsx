import Header from '../components/Header';
import styles from './Map.module.css';
import MapComponent from '../components/MapComponent';
//import Places from '../services/places';

function Map() {

  return (
    <>
        <Header toMap={false}/>
        <div className = { styles.mapContainer }>
          <div className = { styles.map }>
            <MapComponent/> 
          </div> 
        </div>
    </>
  )
}

export default Map
