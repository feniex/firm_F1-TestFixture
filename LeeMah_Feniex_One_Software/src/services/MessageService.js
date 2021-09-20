import axios from 'axios';

const API_URL = ' https://recruiterflow.com';

const options = {
    headers: {'RF-Api-Key': 'ed3b7e9c33f80673401773e361954397', 'Access-Control-Allow-Origin': true,
    'Content-Type': 'multipart/form-data' }
  };

export default class MessageService{

    constructor(){}


    getMessages() {
        const url = `${API_URL}/api/external/candidate/list?current_page=1&items_per_page=100`;
        return axios.get(url, options).then(response => response.data);
    }  
    getMessagesByURL(link){
        const url = `${API_URL}${link}`;
        return axios.get(url).then(response => response.data);
    }
    getMessage(pk) {
        const url = `${API_URL}/api/Candidates/${pk}`;
        return axios.get(url).then(response => response.data);
    }
    deleteMessage(Candidate){
        const url = `${API_URL}/api/Candidates/${Candidate.pk}`;

        return axios.delete(url);
    }
    createMessage(Candidate){
        const url = `${API_URL}/api/Candidates/`;
        return axios.post(url,Candidate);
    }
    updateMessage(Candidate){
        const url = `${API_URL}/api/Candidates/${Candidate.pk}`;
        return axios.put(url,Candidate);
    }
}